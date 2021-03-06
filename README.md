# Assignment 4 - Hunt the Wumpus
**Due by 11:59pm on Monday, 3/4/2018**

**Demos due by 11:59pm on Monday 3/18/2018**

The goal of this assignment is to start working with polymorphism and C++ template classes from the STL.  Follow the directions below, and make sure your source code files (**no executable files, `.o` files, or other crufty stuff**) are committed and pushed back into your repository on GitHub to earn credit for the assignment.

## The Hunt the Wumpus game

Hunt the Wumpus is a game set inside the cave of the Wumpus, a scary, gold-harding monster who likes to eat people who disturb its sleep.  The player's goal is to guide an adventurer to kill the Wumpus, find its hidden gold, and escape alive. The Wumpus lives in a large cave of rooms arranged in a grid, where each room at has four tunnels leading to the rooms to the north, east, south, and west.

The adventurer starts the game in a random empty room in the Wumpus’ cave. Her starting position is also the location of the escape rope that she must use to escape after she's completed her task.

Each room may be empty, or it may contain one (and only one) of four "events" (all described below): two kinds of dangerous hazards, the terrifying Wumpus, and the gold treasure. When the adventurer is in a room that’s adjacent to one containing an "event", the player will receive a percept (a message) to inform them about the event the adventurer is close to.

If the adventurer perishes while searching for the Wumpus, the player should be presented with the option to start the game over with the same cave configuration, start the game over with a new random cave configuration, or quit the game entirely.

The player wins the game if they can safely guide the adventurer through the cave to kill the Wumpus, pick up the gold, and make it back to the escape rope unharmed!

## Game elements

### The adventurer

Each turn you may take one of two actions to guide the adventurer:

  * **Move**: You can move through a tunnel to an adjacent room.

  * **Fire an Arrow**: The adventurer begins the game with three arrows. As long as the adventurer still has at least one arrow, the player can choose to fire one in any direction (i.e. north, south, east, or west). The arrow continues flying in the same direction until it hits a wall or travels through three rooms. If the arrow enters the Wumpus’ room, it pierces the Wumpus’ heart and kills the monster. If the adventurer runs out of arrows without having killed the Wumpus, you lose.

### The Wumpus

Usually, the Wumpus is peacefully asleep in its cave. Two things wake the Wumpus up, however: the adventurer entering its room or shooting an arrow and missing it. If the Wumpus wakes up while in the same room as the adventurer, the Wumpus will angrily eat the adventurer, ending the game. If the Wumpus just wakes up from hearing an arrow being fired, though, there’s a 75% chance it will move to a random empty room in the cave to avoid being found.

### Hazards

There are two kinds of hazards in the Wumpus' cave:

  * **Bottomless pits**: Two of the cave's rooms have bottomless pits in them.  If the adventurer enters a room with a bottomless pit, she falls in and dies, and the player loses.

  * **Super bats**: Two rooms have super bats. If the adventurer enters a room that contains super bats, an angry bat grabs her and takes her to some other room at random (which could be dangerous!).

### The gold

The gold is a treasure sitting in a room that contains neither a hazard nor the wumpus. If the adventurer is in a room containing the gold, she automatically picks it up and takes it with her.

### Percepts

When the adventurer is in a room directly adjacent to to a room containing an "event", the player receives the following messages:

* **Wumpus**: "You smell a terrible stench."
* **Super bats**: "You hear wings flapping."
* **Bottomless pit**: "You feel a breeze."
* **Gold**: "You see a glimmer nearby."

Notice that there’s no percept for the escape rope! That means the player will have to remember where they started and find their way back to that tile after they’ve completed their task.

As an example of how the percepts work, if the adventurer is standing in an empty room with the Wumpus one room to the North, the Gold one room to the East, and Bats *two* rooms to the South, they would receive the following messages at the beginning of their turn:

```
You smell a terrible stench.
You see a glimmer nearby.
```

Remember, the percepts don’t tell you where the hazard or gold is, just that it’s somewhere close!

## Program requirements

* Your program should allow the user to play Hunt the Wumpus, as described above.

* The Wumpus' cave is represented by a square grid.  The size of the grid (i.e. the number of rooms on one side of the square) should be specified **as a command line parameter to your program**.  Caves smaller than four rooms on a side aren't allowed. You should visualize the grid to allow the user to play the game. In particular, you should display the grid, and indicate within the grid which room the player is in.  An example visualization of a 4x4 grid might look like this, where the `*` character represents the location of the adventurer:
    ```
    +---+---+---+---+
    |   |   |   |   |
    |   |   |   |   |
    |   |   |   |   |
    +---+---+---+---+
    |   |   |   |   |
    |   |   |   |   |
    |   |   |   |   |
    +---+---+---+---+
    |   |   |   |   |
    |   |   | * |   |
    |   |   |   |   |
    +---+---+---+---+
    |   |   |   |   |
    |   |   |   |   |
    |   |   |   |   |
    +---+---+---+---+
    ```

* Your code must have the following classes: `Room`, `Event`, `Wumpus`, `Bats`, `Pit`, and `Gold`.  You may create more classes if they would be helpful.

* The `Event` class **must be abstract** (i.e. it must contain purely virtual functions), and the `Wumpus`, `Bats`, `Pit`, and `Gold` classes should all be derived from `Event`.  Remember, any event does something when the adventurer enters the same room as the event, and will display a message when the adventurer is nearby. Your design of the `Event` class should reflect this.  For example, your `Event` class might have a `percept()` method that is called whenever the adventurer is in a room adjacent to the event, where the `Wumpus`, `Bats`, `Pit`, and `Gold` classes implement their own specific versions of the `percept()` method.  Similarly, your `Event` class might have an `encounter()` method that is called when the adventurer enters the same room as the event, with the individual event classes implementing their own specific versions of `encounter()`.

* **You must use the `Event` classes polymorphically.**  In other words, your `Room` class may only contain a member of the `Event` class but not members of the `Wumpus`, `Bats`, `Pit`, or `Gold` classes.

* Each `Room` contains *at most* one `Event`, but it may not contain any `Event`.  The design of your `Room` class should reflect this.

* The grid representing your cave should be implemented using the `std::vector` class.

## Hints

* Polymorphism only works when you are working with references or pointers.  If you use the value of an object directly, it may not select the correct member function.

* Hunt the Wumpus is a game all about hiding information from the player, which might make it hard to debug! To get around this problem, you might want to create a debugging-only map display so that you can tell exactly what’s in the cave while you’re testing your program. Just make sure you disable this before submitting the assignment!

* Hunt the Wumpus is a very common introductory programming project. This assignment, however, is designed to specifically include the programming concepts you’ve seen in this class so far.  It’s very likely that other versions of Hunt the Wumpus you could find do not correctly implement what’s described above.

## Extra credit

For 10 points of extra credit, you can implement an AI class that plays the game for you.  This AI class should use the same interface to the game that the player does.  That is, it should use percepts to learn about the world and make decisions.

## Code style

You must include a header comment for each source code file that contains a description of the file (including how to run the program, command line arguments, etc. if the file contains your `main()` function), your name, and the date.  Your code should be well commented, including header comments for *all* functions describing what the function does, its parameters, and any pre- and post-conditions for the function.  You should appropriately use whitespace, newlines, and indentation.

Make sure you review the style guidelines for the course, and start trying to follow them:

http://web.engr.oregonstate.edu/~hessro/static/media/cs162-style-guidelines.4812c1d9.pdf

## Submitting your program

To submit your program, you need to make sure the following files are committed into your git repository and pushed to your `master` branch on GitHub before the due date above:
  * The `.cpp` file containing your application code.
  * All of the `.hpp` and `.cpp` files containing the interface and implementation of your classes.
  * Your `Makefile`.

Do not commit any other files (other than the ones that were already in your repository at the start of the assignment). A good way to check whether your assignment is submitted is to simply look at your repo on GitHub (i.e. https://github.com/OSU-CS162-W19/assignment-4-YourGitHubUsername). If your files appear there before the deadline, they they are submitted.

## Grading criteria

Your program **MUST** compile and run on `flip.engr.oregonstate.edu`, so make sure you have tested your work there before you make your final submission, since a program that compiles and runs in one environment may not compile and run in another.  **Assignments that do not compile on `flip` will receive a grade of 0.**  If you do not have an ENGR account, you can create one at https://teach.engr.oregonstate.edu/.

This assignment is worth 100 points total:
  * 90 points: your program meets the specifications above
    * 10 points: displays a square cave whose size is set by a command line parameter
    * 10 points: implements `Room` class
    * 20 points: implements abstract `Event` class and derived `Wumpus`, `Bats`, `Pit`, and `Gold` classes
    * 10 points: uses `Event` classes polymorphically
    * 10 points: uses `std::vector` to implement a grid of `Room` objects
    * 10 points: allows the player to move the adventurer through the cave and to shoot up to 3 arrows
    * 5 points: the Wumpus is killed if hit by an arrow and moves to a different room with 75% probability if woken up by an arrow that misses
    * 5 points: adventurer dies if she falls in a pit and is carried to a different room if she encounters bats
    * 5 points: game displays percepts based on adjacent events
    * 5 points: adventurer wins by picking up gold, killing the Wumpus, and escaping

  * 10 points: your code is appropriately commented and uses consistent and appropriate style

Your work on this assignment will be graded by demoing it with a TA.  During your demo, you will compile and run your program for the TA and walk them through your source code, describing to them how it works.  It'll be your responsibility to sign up for a 10-minute demo slot with a TA by the demo due date above.  **You will receive a zero on the assignment if you don't demo it with a TA by the demo due date.**
