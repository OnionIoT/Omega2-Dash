class term:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    WARNING = '\033[93m'
    RED = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    CLEAR = '\033[2J'
    CLEARLINE = '\033[1A\033[2K\033[1A'
    RESET = '\033[0m'

    def red(msg):
        return term.RED + msg + term.ENDC
    def green(msg):
        return term.GREEN + msg + term.ENDC
    def blue(msg):
        return term.BLUE + msg + term.ENDC
    def yellow(msg):
        return term.WARNING + msg + term.ENDC

print(term.red('Having ') + term.blue('a lot ') + term.green('of fun ') + term.yellow('with this!'))
