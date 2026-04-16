# cub3D

_This project was created as part of the 42 curriculum by `jkovacev` and `asalniko`._

## Overview

`cub3D` is a small Wolfenstein 3D-inspired raycaster built with MiniLibX. The program reads a `.cub` scene file, validates its configuration and map, initializes the player from the map, and renders a real-time first-person view with textured walls.

The current project focuses on a clean mandatory implementation:

- `.cub` file parsing with texture and color configuration
- map normalization and validation
- player initialization from `N`, `S`, `E`, or `W`
- per-column raycasting with DDA
- textured wall rendering
- keyboard movement, strafing, rotation, and clean exit handling

## Implemented Features

### Parsing and Validation

The parser currently supports:

- `NO`, `SO`, `WE`, `EA` texture paths
- `F` and `C` RGB colors for floor and ceiling
- maps containing `1`, `0`, spaces, and a single player start position

The validation layer currently checks:

- the program is launched with exactly one `.cub` file
- all required texture paths and both colors are present before the map
- duplicate texture declarations are rejected
- duplicate floor or ceiling color declarations are rejected
- texture files exist and can be opened
- RGB input format is valid and each component is within `0-255`
- only valid map characters are used
- the map contains exactly one player
- the map is closed using a flood-fill style closure check
- empty lines after the map starts are treated as map termination
- any non-map content after the map is rejected

Maps with uneven row lengths are normalized by padding shorter rows with spaces before validation. This allows the closure check to detect leaks through gaps or malformed borders reliably.

### Rendering

The renderer currently includes:

- a `1024x768` window
- frame rendering through an MLX image buffer
- ceiling and floor background fill using parsed RGB colors
- one ray per screen column
- DDA wall hit detection
- wall projection based on perpendicular distance
- texture selection by wall orientation (`north`, `south`, `west`, `east`)
- textured vertical wall slices

### Player Controls

The current controls are:

- `W` move forward
- `S` move backward
- `A` move left
- `D` move right
- `Left Arrow` rotate left
- `Right Arrow` rotate right
- `ESC` close the game
- window close button exits cleanly

Movement is collision-checked against non-walkable cells, so the player cannot move through walls or outside the valid playable area.

## Build and Run

### Compilation

Run in the project root:

```bash
make
```

This builds:

- the main executable `./cub3D`
- bundled `libft`
- bundled `minilibx-linux`

### Execution

Run the program with a valid map:

```bash
./cub3D maps/basic.cub
```

Additional sample maps are available in [`maps/`];

Examples included in the repository:

- valid maps with standard layout and maps containing leading spaces
- invalid maps for open walls
- invalid maps with missing player or multiple players
- invalid maps with bad characters
- invalid color format examples

## Project Structure

- [`main.c`] files parsing, initialization, texture loading, and the MLX loop
- [`parsing/`] contains `.cub` parsing, texture/color parsing, map normalization, and validation
- [`game_init.c`], [`game_init2.c`], [`init_ray.c`], [`init_ray2.c`] , and [`render_background.c`] contain the rendering and movement logic
- [`textures.c`] loads XPM textures and computes texture sampling
- [`libft/`] contains the local C utility library
- [`get_next_line/`] provides line-by-line file reading

## AI Usage Disclosure

This project follows the 42 guidance on responsible AI usage.

AI was used only as a support tool for limited tasks such as:

- documentation drafting and editing
- brainstorming implementation options and project structure
- reducing repetitive work in build-system or text-writing tasks
- clarifying technical concepts during development

AI was not treated as an authority and no generated content was accepted blindly. Any AI-assisted output that was kept in the project was:

- reviewed critically
- discussed with peers when relevant
- tested manually against the actual codebase
- rewritten or adapted until fully understood

# P.S. cub3D Math

A short math reference for the `cub3D` project, tied to the current implementation in this repository.

## 1. Coordinates and the map grid

The map is stored as a 2D grid:

- `map.grid[y][x]`
- `x` grows from left to right
- `y` grows from top to bottom

The player position is stored as floating-point coordinates:

- `player.x`
- `player.y`

If the player start is found at `[row][col]`, the code places the player in the center of that tile:

```c
player.x = col + 0.5;
player.y = row + 0.5;
```

That matters because rays should start from the center of the cell, not from a corner.

## 2. The player's direction vector

The player looks in the direction of:

```text
dir = (dir_x, dir_y)
```

In the current code, the initial direction depends on the map marker:

- `N` -> `(0, -1)`
- `S` -> `(0, 1)`
- `E` -> `(1, 0)`
- `W` -> `(-1, 0)`

This vector defines where the player is facing.

## 3. The camera plane

Besides `dir`, the player also has:

```text
plane = (plane_x, plane_y)
```

This vector is perpendicular to `dir` and defines the width of the camera view.

In the code:

```c
player.plane_x = -game->player.dir_y * tan((FOV * PI / 180.0) / 2.0);
player.plane_y = game->player.dir_x * tan((FOV * PI / 180.0) / 2.0);
```

Why this works:

- if `dir = (dx, dy)`, then a perpendicular vector is `(-dy, dx)`
- the camera plane length is computed as tan(FOV / 2), which sets the view width

## 4. One ray per screen column

The screen is rendered column by column. For each `x` from `0` to `WIN_WIDTH - 1`, one ray is computed.

First, convert the screen column into the range `[-1, 1]`:

```c
camera_x = 2 * x / (double)WIN_WIDTH - 1;
```

Interpretation:

- `camera_x = -1` -> left edge of the screen
- `camera_x = 0` -> center of the screen
- `camera_x = 1` -> right edge of the screen

Then compute the ray direction:

```c
ray.dir_x = player.dir_x + player.plane_x * camera_x;
ray.dir_y = player.dir_y + player.plane_y * camera_x;
```

Meaning:

- the center ray goes straight along `dir`
- left and right rays are shifted along `plane`

## 5. Which map cell the ray starts in

The ray starts from the player position, but DDA works on map cells:

```c
ray.map_x = (int)player.x;
ray.map_y = (int)player.y;
```

That means: take the map cell that currently contains the player.

## 6. Delta distance

We need to know how far the ray travels:

- from one vertical grid line to the next
- from one horizontal grid line to the next

In the code:

```c
ray.delta_x = fabs(1 / ray.dir_x);
ray.delta_y = fabs(1 / ray.dir_y);
```

Idea:

- `delta_x` is how much ray length increases when moving by one cell in `x`
- `delta_y` is how much ray length increases when moving by one cell in `y`

If `ray.dir_x == 0` or `ray.dir_y == 0`, the code uses a very large number `1e30` to avoid division by zero.

## 7. Step and initial side distance

We also need to know in which direction the ray moves through the grid:

- along `x`: left or right
- along `y`: up or down

### Along the X axis

If the ray points left:

```c
step_x = -1;
side_x = (player.x - map_x) * delta_x;
```

If it points right:

```c
step_x = 1;
side_x = (map_x + 1.0 - player.x) * delta_x;
```

### Along the Y axis

If the ray points up:

```c
step_y = -1;
side_y = (player.y - map_y) * delta_y;
```

If it points down:

```c
step_y = 1;
side_y = (map_y + 1.0 - player.y) * delta_y;
```

Meaning:

- `side_x` is the distance from the player to the first vertical grid boundary
- `side_y` is the distance from the player to the first horizontal grid boundary

## 8. DDA - Digital Differential Analyzer

DDA compares:

- `side_x`
- `side_y`

If `side_x < side_y`, the ray reaches a vertical grid boundary first:

```c
side_x += delta_x;
map_x += step_x;
side = 0;
```

Otherwise it reaches a horizontal grid boundary first:

```c
side_y += delta_y;
map_y += step_y;
side = 1;
```

After each step, the code checks whether the ray hit a wall.

Meaning of `side`:

- `side == 0` -> the ray hit a vertical side of a cell
- `side == 1` -> the ray hit a horizontal side of a cell

This is later used for both distance computation and texture selection.

## 9. Distance to the wall

After DDA, the ray has already entered the wall cell. We now need the distance to the actual hit point.

In the code:

```c
if (ray.side == 0)
    ray.dist = ray.side_x - ray.delta_x;
else
    ray.dist = ray.side_y - ray.delta_y;
```

Why subtract `delta`:

- the last DDA step already moved us into the wall cell
- `side_x` or `side_y` now points past the hit boundary
- so we step back by one grid increment

This is the perpendicular camera distance, not the raw diagonal ray length. That is what avoids the fish-eye effect.

## 10. Projecting the wall onto the screen

The closer the wall is, the taller it appears on screen.

Line height:

```c
ray.height = (int)(WIN_HEIGHT / ray.dist);
```

Top and bottom of the wall stripe:

```c
ray.start = -ray.height / 2 + WIN_HEIGHT / 2;
ray.end   =  ray.height / 2 + WIN_HEIGHT / 2;
```

Meaning:

- the wall is vertically centered on the screen
- a near wall gives a large `height`
- a far wall gives a small `height`

## 11. Exact wall hit position

To choose the correct texture column, we need the fractional hit position on the wall.

In the code:

```c
if (ray.side == 0)
    ray.wall_x = player.y + ray.dist * ray.dir_y;
else
    ray.wall_x = player.x + ray.dist * ray.dir_x;
ray.wall_x -= floor(ray.wall_x);
```

After subtracting `floor()`, only the fractional part remains:

```text
wall_x in [0, 1)
```

This is the position inside the wall segment:

- `0.0` -> left edge of the texture
- `0.5` -> middle
- `0.99` -> almost the right edge

## 12. Choosing the texture by wall orientation

In the current code:

- if `side == 0` and `dir_x > 0` -> `east`
- if `side == 0` and `dir_x < 0` -> `west`
- if `side == 1` and `dir_y > 0` -> `south`
- if `side == 1` and `dir_y < 0` -> `north`

So:

- the `x` direction decides east/west
- the `y` direction decides north/south

## 13. Texture X coordinate

Once `wall_x` is known, the texture column is:

```c
ray.tex_x = (int)(ray.wall_x * tex->img.width);
```

Sometimes the texture needs to be mirrored:

```c
if (ray.side == 0 && ray.dir_x > 0)
    ray.tex_x = tex->img.width - ray.tex_x - 1;
if (ray.side == 1 && ray.dir_y < 0)
    ray.tex_x = tex->img.width - ray.tex_x - 1;
```

This keeps the texture from appearing flipped depending on which side the ray hits.

## 14. Texture Y coordinate

The texture has to be stretched or compressed to fit the wall stripe height.

Texture step:

```c
ray.step = 1.0 * tex->img.height / ray.height;
```

Starting position:

```c
ray.tex_pos = (ray.start - WIN_HEIGHT / 2 + ray.height / 2) * ray.step;
```

For each screen pixel:

```c
ray.tex_y = (int)ray.tex_pos;
ray.tex_pos += ray.step;
```

Meaning:

- if the wall is tall, `step` is small, so the texture is sampled more slowly
- if the wall is short, `step` is large, so the texture is sampled faster

## 15. Rotating the player

Rotation uses the standard 2D rotation matrix.

Formula:

```text
x' = x * cos(a) - y * sin(a)
y' = x * sin(a) + y * cos(a)
```

The code applies the same rotation to both `dir` and `plane`:

```c
new_dir_x = dir_x * cos(a) - dir_y * sin(a);
new_dir_y = old_dir_x * sin(a) + dir_y * cos(a);
```

If only `dir` were rotated and `plane` were not, the camera would become inconsistent and the rendered image would break.

## 16. Forward and backward movement

Moving forward:

```c
player.x += dir_x * speed;
player.y += dir_y * speed;
```

Moving backward:

```c
player.x -= dir_x * speed;
player.y -= dir_y * speed;
```

In this project, collision checks are done separately per axis:

```c
if (cell along x is walkable)
    player.x += dir_x * move;
if (cell along y is walkable)
    player.y += dir_y * move;
```

That is useful because it lets the player slide along walls instead of getting completely stuck on diagonal collisions.

## 17. Strafing

Strafing uses `plane`, not `dir`, because `plane` is perpendicular to the view direction:

```c
player.x += plane_x * move;
player.y += plane_y * move;
```

So:

- `A` moves left relative to the camera
- `D` moves right relative to the camera
