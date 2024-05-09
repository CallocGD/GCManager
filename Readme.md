# GCManager 

A Garbage Collector Manager written in C++ binded from another gc library and then I modified it with mimalloc. 
Inspried by the many Reverse Engineered Snippets of Geometry dash code. This is designed to replace any cocos2d gc styled things. 
(Many will say this is a stupid idea but I really do not care.)


# Story
So JohnP55 and I were looking through my ghidra project of the game on a discord vc call and we found that cocos2d has 
poor dogshit memory management, so a couple of days later, I came up with an idea to implement a c++ garbage collector 
into the game and Other tools like mimalloc for a performance boost in a future mod to hopefully fix memory leaks 
with cocos2d in general in the hopes that Geometry dash runs a bit smoother. 

Robtop, if you are looking at this, I encorage you to try and implement something like this in the future as 
it might be extremely helpful for performance gains. 

