#pragma once

#include <array>

enum class TetrominoType
{
    I,
    O,
    T,
    S,
    Z,
    J,
    L
};

struct Cell
{
    int x;
    int y;
};

struct TetrominoDefinition
{
    std::array<std::array<Cell, 4>, 4> rotations;
};

inline constexpr TetrominoDefinition I_PIECE =
{
    {{
        {{
            {0,1}, {1,1}, {2,1}, {3,1}
        }},
        {{
            {2,0}, {2,1}, {2,2}, {2,3}
        }},
        {{
            {0,2}, {1,2}, {2,2}, {3,2}
        }},
        {{
            {1,0}, {1,1}, {1,2}, {1,3}
        }}
    }}
};

inline constexpr TetrominoDefinition O_PIECE =
{
    {{
        {{
            {1,0}, {2,0}, {1,1}, {2,1}
        }},
        {{
            {1,0}, {2,0}, {1,1}, {2,1}
        }},
        {{
            {1,0}, {2,0}, {1,1}, {2,1}
        }},
        {{
            {1,0}, {2,0}, {1,1}, {2,1}
        }}
    }}
};

inline constexpr TetrominoDefinition T_PIECE =
{
    {{
        {{
            {1,0}, {0,1}, {1,1}, {2,1}
        }},
        {{
            {1,0}, {1,1}, {2,1}, {1,2}
        }},
        {{
            {0,1}, {1,1}, {2,1}, {1,2}
        }},
        {{
            {1,0}, {0,1}, {1,1}, {1,2}
        }}
    }}
};

inline constexpr TetrominoDefinition S_PIECE =
{
    {{
        {{
            {1,0}, {2,0}, {0,1}, {1,1}
        }},
        {{
            {1,0}, {1,1}, {2,1}, {2,2}
        }},
        {{
            {1,1}, {2,1}, {0,2}, {1,2}
        }},
        {{
            {0,0}, {0,1}, {1,1}, {1,2}
        }}
    }}
};

inline constexpr TetrominoDefinition Z_PIECE =
{
    {{
        {{
            {0,0}, {1,0}, {1,1}, {2,1}
        }},
        {{
            {2,0}, {1,1}, {2,1}, {1,2}
        }},
        {{
            {0,1}, {1,1}, {1,2}, {2,2}
        }},
        {{
            {1,0}, {0,1}, {1,1}, {0,2}
        }}
    }}
};

inline constexpr TetrominoDefinition J_PIECE =
{
    {{
        {{
            {0,0}, {0,1}, {1,1}, {2,1}
        }},
        {{
            {1,0}, {2,0}, {1,1}, {1,2}
        }},
        {{
            {0,1}, {1,1}, {2,1}, {2,2}
        }},
        {{
            {1,0}, {1,1}, {0,2}, {1,2}
        }}
    }}
};

inline constexpr TetrominoDefinition L_PIECE =
{
    {{
        {{
            {2,0}, {0,1}, {1,1}, {2,1}
        }},
        {{
            {1,0}, {1,1}, {1,2}, {2,2}
        }},
        {{
            {0,1}, {1,1}, {2,1}, {0,2}
        }},
        {{
            {0,0}, {1,0}, {1,1}, {1,2}
        }}
    }}
};

inline constexpr std::array<TetrominoDefinition, 7> kTetrominos =
{
    I_PIECE,
    O_PIECE,
    T_PIECE,
    S_PIECE,
    Z_PIECE,
    J_PIECE,
    L_PIECE
};