# Structure
I was just thinking that with this immediate mode gui code we are going to have in the lua stuff, there is actually no
need to have any different game scenes in this game. However, actually that is incorrect because if this engine is
expanded to allow extra play modes they will need their own scene.

# repository
I must make the bullet manager a global thing because otherwise we will be making memory for it all the time which would
suck as it's massive. Yeah so it is global so there is not any need to worry about things like where the bullets are
stored as it can store them.

I was also thinking about the repository system for assets which will indeed be necessary. I will do my usual lazy load
approach where whenever we load sprites or spritesheets we should do it through a method call on the repository and it
will from then on save it with the filename as key so next time you want to load it it just returns it. This also means
you do not need to worry about memory leaks as they are all intentionally stored and then freed at the end.

Hypothetically if we ever had memory problems I could just make the repository strategically free large images that are
not being used. Actually in order to do that I would need to use one of those special pointers that counts references so
maybe I can't be bothered but I doubt that is going to be an issue so who gives a frick.

Also I should add a method which loads an image texture without saving it for world backgrounds as those are going to be
quite large and cycled through quite a lot without all that much reuse.
