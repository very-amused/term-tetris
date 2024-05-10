# CS202 Capstone Writeup

Name - Keith Scroggs
Group - Started with Larry Wang and Charlie Boddicker, ended solo. Nothing personal: this project is a reach and my group members were reasonable in communicating me that they would be more comfortable implementing something more simple.

## Building & Running
```sh
# Clean build files
make clean
# Build (release)
make
# Build (debug - NOT FOR LAB EVALUATION)
make clean; make debug

# Run
make run # or just ./build/tetris
```

## Time Logging
I've spent from early morning to shy of midnight yesterday and today on this project.
Tuesday: something
Wednesday: 7AM-10PM = 15hr - 30m lunch = 14.5 hr
Thursday: 9AM-11PM = 14hr - 30m lunch = 13.5 hr

I have spent 28 hours of the past 48 on this. There is evidence of more work that can be seen in the [Commit History](https://github.com/very-amused).
All commits containing my work are signed by my GPG public key, which can be verified in GitHub itself.

## The Writeup
This project has been a nice way to learn how freehanding C++ feels. On the self-critical front, there's definitely some garbage code in here, mostly pertaining to Tetromino (piece) decomposition and row clearing. Feel free to play find the memory leak (hint: `rg '\(void\)'`). I don't like how the rushed parts of this turned out, and I'm going to go back and fix them.

On a more positive note, I'm still happy with the product of what I was able to get done thusfar. The physics and collision work flawlessly, the block decomposition both fixes rendering bugs and makes row clearing a lot more doable. The systems I've set up for movement, input handling, and rendering are all organized well enough that cleaning up decomposition and making this more into a real thing (block rotation, score counting, clear animations, the halting problem).

### My case for full discretionary points:
- ncurses for full color terminal graphics
- Fixed-clock game loop with frame-counter driven gravity
- Bitmap 2D collision system
- C++11 `std::uniform_int_distribution` + Mersenne Twister RNG for pieces and colors
- Input debouncing and hold support
- Piece to row decomposition on block placement (this was **not** easy to sort out and implement. I have even more respect for the gamedevs that walk among us mortals now)
- Full rows clear, rows above clears drop as expected
