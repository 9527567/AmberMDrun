import argparse
import pyamber as pya
import os
def main():
    parser = argparse.ArgumentParser(description='Demo of argparse')
    parser.add_argument('--epochs', type=int, default=30)
    parser.add_argument('--batch', type=int, default=4)
    args = parser.parse_args()
    print(args)
if __name__ == '__main__':
    main()
