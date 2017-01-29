# Use GPIO pins 13, 15, 16, 18

import readline
from cmd import Cmd

class ControllerShell(Cmd):
    intro = "Starting motor controller"
    prompt = "(motor-control): "

    def do_up(self, arg):
        print("up")
    
    def do_down(self, arg):
        print("down")

shell = ControllerShell()
shell.cmdloop()
