Tunnelman
A video game based on the old arcade game 'Dig Dug', circa 1982

Description
‣ The object of the game is to find all hidden Oil Barrel objects and proceed to the next level without getting caught by the AI, also known as the Protesters 

‣ The Regular Protesters (in dark blue) only follow the player when you, the Frackman (holding a pickaxe), are in their line of sight 

‣ The Hardcore Protesters (in overalls) calculate your current location during every tick of the game and derive the shortest possible path towards you 

‣ Everytime a Protester comes close to your location, you will lose health. Once your health drops to 0%, you lose the game 

Design
‣ Implemented the game using C++, exhibiting concepts such as polymorphism, inheritance, and encapsulation 

‣ Designed a method for the AI to follow the location of the player on the grid with a recursive, queue-based algorithm that performs a breadth-first search 

‣ Devised a hierarchy of game objects to distinguish the different objects and store them in a single array under a universal superclass to prevent code duplication 

‣ Developed an algorithm to raise the difficulty of each level by periodically increasing the number of Oil Barrels, Protesters, and Boulders on the grid 
