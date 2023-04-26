# CS1010301-MineSweeper-Project
 111.2 CS1010301 物件導向程式設計實習 踩地雷遊戲.  
 MineSweeper game with GUI supported, writing in C++.  
 <img width="868" alt="截圖 2023-04-23 上午7 55 57" src="https://user-images.githubusercontent.com/31580253/234451668-15293e6a-b9d6-4c85-b69a-f1e741adb53f.png">

## Support Platforms
 - Windows MSVC
 - MacOS AppleClang
 - Linux GCC/Clang
 > ⚠️ Apple Silicon (arm64) is not currently supported.

## Build
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

## Run Mode
The game support in console mode and GUI mode.  
We can use launch arguments to run the game in different mode.  
By default run the game it running in GUI mode.  
### Command Input
```bash
./MineSweeper CommandInput
```
### Command File
```bash
./MineSweeper CommandFile <InputCommandFile> <OutputResultFile>
```
### GUI
```bash
./MineSweeper GUI
```

## Game State
<img width="781" alt="image" src="https://user-images.githubusercontent.com/31580253/234464293-62be78a8-24e2-4d74-9960-65d4d4da0556.png">

 - Standby
 - Playing
 - GameOver

## Command
| Command      | Usage                              | Standby | Playing | GameOver |
| ------------ | ---------------------------------- | ------- | ------- | -------- |
| `Load`       | Load game board                    | ✅       |         |          |
| `StartGame`  | Start game                         | ✅       |         |          |
| `Print`      | Print the information              | ✅       | ✅       | ✅        |
| `LeftClick`  | Left click a block (Uncover block) |         | ✅       |          |
| `RightClick` | Right click a block (Put flag)     |         | ✅       |          |
| `Replay`     | Start a new game                   |         |         | ✅        |
| `Quit`       | Quit game                          |         |         | ✅        |

### Load
```
Load <Load Mode...>
```

#### Load Mode
##### BoardFile
Load the generated board file
```
Load BoardFile <file_path>
```

###### Example
```
Load BoardFile ./boards/board1.txt
```

##### RandomCount
Generate a board with random count mines
 ```
Load RandomCount <width> <height> <mines_count>
 ```

###### Example
```
Load RandomCount 10 10 10
```

##### RandomRate
Generate a board with random rate mines
```
Load RandomRate <width> <height> <mines_rate>
```

###### Example
```
Load RandomRate 10 10 0.3
```

### Print
```
Print <Print Mode...>
```

#### Print Mode
##### GameBoard
Current game board
- Covered block `#`
- Uncovered block `number`
- Flag `f`
- Question Mark `?`
- Mine `X`

###### Example Input
```
Print GameBoard
```

###### Example Output
```
0 0 0 0 0 0 0 0 1 # 
0 0 0 0 0 0 0 0 1 1 
1 1 1 0 0 0 0 0 0 0 
# f 1 0 1 1 2 1 1 0 
1 1 1 0 1 # ? # 2 1 
0 0 0 0 1 1 # # # # 
0 0 0 0 0 1 # # # # 
0 0 0 0 1 2 # # # # 
1 2 1 1 1 # # # # # 
# # # # # # # # # # 
```

##### GameAnswer
###### Example Input
```
Print GameAnswer
```

###### Example Output
```
0 0 0 0 0 0 0 0 1 X 
0 0 0 0 0 0 0 0 1 1 
1 1 1 0 0 0 0 0 0 0 
1 X 1 0 1 1 2 1 1 0 
1 1 1 0 1 X 2 X 2 1 
0 0 0 0 1 1 2 1 2 X 
0 0 0 0 0 1 1 1 1 1 
0 0 0 0 1 2 X 1 0 0 
1 2 1 1 1 X 3 2 0 0 
X 2 X 1 1 2 X 1 0 0 
```

##### GameState
Current game state (Standby/Playing/GameOver).

##### BombCount
Current bomb(mines) count in the board.

##### FlagCount
Current flags count in the board.

##### OpenBlankCount
Current uncovered block count in the board.

##### RemainBlankCount
Current covered block count in the board.

## Screenshoot
### Console
<img width="1011" alt="截圖 2023-04-26 上午11 33 46" src="https://user-images.githubusercontent.com/31580253/234463356-29ca9a34-11d2-42ea-9086-c2b2c4c0ee35.png">

### GUI
<img width="868" alt="截圖 2023-04-23 上午7 54 53" src="https://user-images.githubusercontent.com/31580253/234449563-8a3cb2d3-7bab-4b17-b3e7-d960dfb1eaf5.png">
<img width="868" alt="截圖 2023-04-23 上午7 55 57" src="https://user-images.githubusercontent.com/31580253/234449594-89f51c7b-1724-432e-9597-eaa1ca8f02e3.png">
<img width="868" alt="截圖 2023-04-23 上午7 54 26" src="https://user-images.githubusercontent.com/31580253/234449858-138f1379-2215-4a5b-9124-b3a1e10191dc.png">
<img width="868" alt="截圖 2023-04-23 上午7 54 26" src="https://user-images.githubusercontent.com/31580253/234449905-92a65b48-28d9-45aa-85c9-cc8b4e060beb.png">
<img width="868" alt="截圖 2023-04-23 上午7 55 24" src="https://user-images.githubusercontent.com/31580253/234449965-5b32774a-7c07-4f1f-9e9f-1f61772d15a8.png">
<img width="868" alt="截圖 2023-04-23 上午7 55 15" src="https://user-images.githubusercontent.com/31580253/234449976-c441d4d1-d7b7-4b60-98de-2e1582912636.png">
<img width="868" alt="截圖 2023-04-23 上午7 54 38" src="https://user-images.githubusercontent.com/31580253/234449990-08a5d0c5-596d-4e06-93a0-41c11d3343c6.png">

## Demo Video
[Watch on YouTube](https://youtu.be/PEyo_t_J6iI)
