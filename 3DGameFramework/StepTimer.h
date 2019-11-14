// StepTimer.h - 経過時間情報を提供するシンプルタイマー

#pragma once
#ifndef DX_HELPER_DEFINED
#define DX_HELPER_DEFINED

#include <windows.h>
#include <stdexcept>
#include <exception>
#include <stdint.h>

namespace DX
{
    // アニメーションとシミュレーションタイミングのためのヘルパクラス
    class StepTimer
    {
    public:
        StepTimer() : 
            m_elapsedTicks(0),
            m_totalTicks(0),
            m_leftOverTicks(0),
            m_frameCount(0),
            m_framesPerSecond(0),
            m_framesThisSecond(0),
            m_qpcSecondCounter(0),
            m_isFixedTimeStep(false),
            m_targetElapsedTicks(TicksPerSecond / 60)
        {
            if (!QueryPerformanceFrequency(&m_qpcFrequency))
            {
                throw std::exception( "QueryPerformanceFrequency" );
            }

            if (!QueryPerformanceCounter(&m_qpcLastTime))
            {
                throw std::exception( "QueryPerformanceCounter" );
            }

            // 1/10秒への最大デルタを初期化する
            m_qpcMaxDelta = m_qpcFrequency.QuadPart / 10;
        }
		
        // 直前のUpdateの呼び出し後経過時間を取得する
        uint64_t GetElapsedTicks() const { return m_elapsedTicks; }
        double GetElapsedSeconds() const { return TicksToSeconds(m_elapsedTicks); }

        // プログラム開始後のトータル時間を取得する
        uint64_t GetTotalTicks() const { return m_totalTicks; }
        double GetTotalSeconds() const { return TicksToSeconds(m_totalTicks); }

        // プログラム開始後のトータルUpdate数を取得する
        uint32_t GetFrameCount() const { return m_frameCount; }

        // 現在のフレームレイトを取得する
        uint32_t GetFramesPerSecond() const { return m_framesPerSecond; }

        // 固定または変動ステップモードを使用するかどうかを設定する
        void SetFixedTimeStep(bool isFixedTimestep) { m_isFixedTimeStep = isFixedTimestep; }

        // 固定時間ステップモード時のUpdateの呼び出し頻度を設定する
        void SetTargetElapsedTicks(uint64_t targetElapsed) { m_targetElapsedTicks = targetElapsed; }
        void SetTargetElapsedSeconds(double targetElapsed) { m_targetElapsedTicks = SecondsToTicks(targetElapsed); }

        // 整数形式は1秒に対する10,000,000テックを使用する時間を示す
        static const uint64_t TicksPerSecond = 10000000;

        static double TicksToSeconds(uint64_t ticks) { return static_cast<double>(ticks) / TicksPerSecond; }
        static uint64_t SecondsToTicks(double seconds) { return static_cast<uint64_t>(seconds * TicksPerSecond); }

        // ブロッキングIO操作など不連続なタイミングの後、キャッチアップ用のUpdate呼び出しを
		// おこない固定タイムステップロジックの保持を避けるためこの関数を呼び出す
        void ResetElapsedTime()
        {
            if (!QueryPerformanceCounter(&m_qpcLastTime))
            {
                throw std::exception("QueryPerformanceCounter");
            }

            m_leftOverTicks = 0;
            m_framesPerSecond = 0;
            m_framesThisSecond = 0;
            m_qpcSecondCounter = 0;
        }

        // 指定された更新関数を呼び出すタイマーの状態を更新する
        template<typename TUpdate>
        void Tick(const TUpdate& update) 
		{
            // 現在の時間を問い合わせる
            LARGE_INTEGER currentTime;

            if (!QueryPerformanceCounter(&currentTime)) 
			{
                throw std::exception( "QueryPerformanceCounter" );
            }

            uint64_t timeDelta = currentTime.QuadPart - m_qpcLastTime.QuadPart;

            m_qpcLastTime = currentTime;
            m_qpcSecondCounter += timeDelta;

            // 大きなデルタタイムをクランプする(例:デバッグのポーズ後)
            if (timeDelta > m_qpcMaxDelta) 
			{
                timeDelta = m_qpcMaxDelta;
            }

            // QPCユニットを標準的なテック形式に変換する
			// 直前のクランプのためオーバーフローはできない
            timeDelta *= TicksPerSecond;
            timeDelta /= m_qpcFrequency.QuadPart;

            uint32_t lastFrameCount = m_frameCount;

            if (m_isFixedTimeStep) 
			{
                // 固定タイムステップ更新ロジック

                // If the app is running very close to the target elapsed time (within 1/4 of a millisecond) just clamp
                // the clock to exactly match the target value. This prevents tiny and irrelevant errors
                // from accumulating over time. Without this clamping, a game that requested a 60 fps
                // fixed update, running with vsync enabled on a 59.94 NTSC display, would eventually
                // accumulate enough tiny errors that it would drop a frame. It is better to just round 
                // small deviations down to zero to leave things running smoothly.

                if (abs(static_cast<int64_t>(timeDelta - m_targetElapsedTicks)) < TicksPerSecond / 4000) 
				{
                    timeDelta = m_targetElapsedTicks;
                }

                m_leftOverTicks += timeDelta;

                while (m_leftOverTicks >= m_targetElapsedTicks) 
				{
                    m_elapsedTicks = m_targetElapsedTicks;
                    m_totalTicks += m_targetElapsedTicks;
                    m_leftOverTicks -= m_targetElapsedTicks;
                    m_frameCount++;

                    update();
                }
            }
            else 
			{
                // 変動タイムステップ更新ロジック
                m_elapsedTicks = timeDelta;
                m_totalTicks += timeDelta;
                m_leftOverTicks = 0;
                m_frameCount++;

                update();
            }

            // 現在のフレームレイトをトラックする
            if (m_frameCount != lastFrameCount) 
			{
                m_framesThisSecond++;
            }

            if (m_qpcSecondCounter >= static_cast<uint64_t>(m_qpcFrequency.QuadPart)) 
			{
                m_framesPerSecond = m_framesThisSecond;
                m_framesThisSecond = 0;
                m_qpcSecondCounter %= m_qpcFrequency.QuadPart;
            }
        }

    private:
        // QPCユニットを使用するためのソースタイミングデータ
        LARGE_INTEGER m_qpcFrequency;
        LARGE_INTEGER m_qpcLastTime;
        uint64_t m_qpcMaxDelta;

        // 標準的なテック形式を使用するための派生タイミングデータ
		uint64_t m_elapsedTicks;
        uint64_t m_totalTicks;
        uint64_t m_leftOverTicks;

        // フレームレイトをトラッキングするための変数
        uint32_t m_frameCount;
        uint32_t m_framesPerSecond;
        uint32_t m_framesThisSecond;
        uint64_t m_qpcSecondCounter;

        // 固定タイムステップモードを構成するための変数
        bool m_isFixedTimeStep;
        uint64_t m_targetElapsedTicks;
    };
}

#endif	// DX_HELPER_DEFINED

