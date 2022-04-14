# NFT Image Generator

## What are NFTs?
"NFT" means "non-fungible token", it's a non-interchangeable unit of data stored on a blockchain, a form of digital ledger, that can be sold and traded.

## What does this tool do?
This command line tool allows you to generate a collection of NFTs based on source images that you provide. 
This program will mix the images you gave as input and generate all the possible combinations.

This tool is intended to be used for pixel art only, using it with other kinds of artwork won't yield a good result.
## Building
This program was originally written and tested on Linux however there is a good chance 
it can build on Windows without problems as it doesn't use any libraries outside of the C standard.

Building this tool is very straightforward. 
type this command in the source directory:
`gcc main.c img.c -o nftGen`

## Usage
To use this tool you have to enter the images you want to use as parameters.
Every image *has* to be in the bitmap format (BMP) .
All the images need to have the same size.

To make transparent images you have to use this specific color for the background:
- ![](https://via.placeholder.com/15/ff00ff/000000?text=+) `#ff00ff`

Images are divided in **sets**
A set is a group of images, every time the program needs to generate an image it 
takes one from each set. 

To separate images in sets you can use the minus sign "**-**"
## An example
You'll notice the source directory also contains some images.
Let's try using those images to generate some NFTs.

First of all, we want the background (bg.bmp) to always be present in each result image
so we need to place it in a set by itself, in this way the program will always pick it.

We put the background first because the images get merged in the order you typed them, if we placed the 
background last it would cover everything else and each image would just be blue.

After the background, we add all the other images we want to use.

The command looks like this:
  `  ./nftGen  bg.bmp - head1.bmp head2.bmp - hat1.bmp hat2.bmp hat3.bmp - face1.bmp face2.bmp`

Entering the command will start the generating process, you will get a list of 
all the images generated.
```
 Generating images...
[1/16] out/img01.bmp
[2/16] out/img02.bmp
[3/16] out/img03.bmp
[4/16] out/img04.bmp
[5/16] out/img05.bmp
[6/16] out/img06.bmp
[7/16] out/img07.bmp
[8/16] out/img08.bmp
[9/16] out/img09.bmp
[10/16] out/img10.bmp
[11/16] out/img11.bmp
[12/16] out/img12.bmp

 All images generated successfully.
```
You can find the output images in the folder called "out".

## My opinion on NFTs

NFTs are a type of art that is made for the only purpose of being sold, most NFTs don't have a thought behind them but are randomly generated so that they can be sold in large quantities.

NTFs were originally made with the intent to protect artists but eventually, they ended up doing the opposite.
Tons of original artworks get stolen and turned into NFTs without the original artist's consent.

Not only most NFTs are just awful to look at but they also have a negative impact on the environment.

<ins>I didn't make this tool with the intent of helping people make NFTs</ins>, there are plenty of NFTs generators online that are way better than this simple command tool I made in a few hours.
The reason I made this is because I enjoy programming and I wanted to try something new.

