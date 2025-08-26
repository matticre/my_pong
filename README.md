# My Pong

This is a Pong game I created from scratch using **C++** and the **SFML** library. The project was a great opportunity to learn about key concepts in game development.

Through this project, I gained experience with:

  * **Object-oriented programming:** Designing and implementing classes for different game elements like the `Ball`, `Paddle`, `Score`, and `Menu`.
  * **2D physics:** Handling the movement of the ball and paddles.
  * **2D collision detection:** Implementing logic to detect when the ball hits the walls or a paddle and responding accordingly.

-----

## How to Play

### Dependencies

This project requires the **SFML library** to be installed on your system. The CMake configuration is set up to find the necessary components: `graphics`, `window`, `system`, and `audio`.

### Commands

The easiest way to build and run the game is by using the provided `run.sh` script. This script will create a build directory, run CMake to configure the project, compile the code, and then execute the game.

```bash
./run.sh
```

**Game Controls:**

  * **Player 1 (Left Paddle):** `W` and `S` keys to move up and down.
  * **Player 2 (Right Paddle):** `Up` and `Down` arrow keys to move up and down.
  * **Start/Reset Ball:** Press `Space` to launch the ball.
  * **Quit Game:** Press `Escape` at any time to exit the game.

-----

### Acknowledgments

  * The sound effects for the paddle and wall hits were foung at https://freesound.org/people/NoiseCollector/.
  * The font used for the score and menu is `DejaVuSansMono.ttf`.