_This project has been created as part of the 42 curriculum by jkovacev and asalniko_

# Description

- This project is inspired by the world-famous Wolfenstein 3D game, which is considered the first FPS (first-person shooter) ever created.
- The goal is to make a dynamic view inside a maze from a first-person perspective, using the principles of ray-casting.
- The program parses a ```.cub``` scene description file to extract texture paths and map data to render a 3D environment in real-time.

# Instructions

## Compilation

- To compile the project, run the following command in the root directory: ```make```
- This will generate the ```cub3d``` executable.

## Installation and/or Execution

- To run the program, provide a map file as an argument:
	```./cub3d maps/map.cub```

# Resources

### Documentation and Tutorials

- **Github Markdown Syntax**: [Basic writing and formatting syntax](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax) used for structuring this README

### AI Usage Disclosure

In accordance with project requirements, AI was used for the following tasks:
- **Code Structuring**: Brainstorming the division of labor between Parsing (handled by ```jkovacev```) and Rendering (handled by ```asalniko```).
- **Makefile Optimization**: Assisting in creating a modular build system that handles subdirectories (e.g., ```parsing/```, ```get_next_line/```) and object file management.