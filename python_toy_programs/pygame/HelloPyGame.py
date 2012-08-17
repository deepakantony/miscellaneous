#!/usr/bin/python

import pygame, sys
from pygame.locals import *

def main():
    # initialize
    pygame.init()
    # size of the window
    DISPLAYSURF = pygame.display.set_mode((500, 500))
    # title bar
    pygame.display.set_caption("Hello World!")
    while True: # main loop 
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
        # draw on screen all the time
        pygame.display.update()

if __name__ == "__main__":
    main()
