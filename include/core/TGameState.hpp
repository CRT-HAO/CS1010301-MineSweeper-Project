/**
 *  File: TGameState.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/04/20 01:36:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/04/26 12:56:31
 *  Description: Game State Type Definition
 */

#pragma once

namespace minesweeper
{

    enum class TGameState
    {
        Standby,
        Playing,
        GameOver,
    };

}
