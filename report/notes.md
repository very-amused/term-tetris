# Notes

[Tetris Wiki](https://tetris.fandom.com/wiki/Glossary) has some insanely helpful gameplay details.

## Fixed Clock

The game runs on a single fixed clock loop. Each tick executes a frame. We're going to use a fixed *60hz* clock, as that is plenty to keep up with the step-driven motion in the Tetris gameplay loop.


## Init Logic
```
ARE.fp = 18 # NES tetris appearance delay is 18 frames
ARE.fc = ARE.fp
```

## Frame Logic

Each frame contains the following steps, in order:

ARE - appearance delay
fc - frame counter
fp - frame period

### ARE
1. If !state.ARE: goto drop
2. If ARE.fc == 0: G.fc = 0, state.ARE = false, goto drop
3. If !block: block = genblock()
4. ARE.fc--
5. goto end

### Drop
1. If debounce(input.rotate): block.rotate()
3. for i in input.translate: if debounce(i): block.translate(i)
#### Gravity
4. input.soft_drop: G.fp = 2, G.fc %= G.fp; else G.fp = {level.G.fp}
5. If G.fc > 0: G.fc--, goto end
6. If !block.drop(): state.ARE = true, ARE.fc = ARE.fp, goto end
7. G.fc = G.fp

### End
1. Sleep until next frame
