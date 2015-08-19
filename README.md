bmp\_encoder
============

This is my final project from a computer science class I took as an
undergraduate. It encodes messages in the lowest bits of BMP files.


```
$ echo 'hello world' > msg.txt
$ bmp_encoder msg.txt pic.bmp encoded-pic.bmp
$ > decoded-msg.txt
$ bmp_encoder encoded-pic.bmp decoded-msg.txt
$ cat decoded-msg.txt
hello world
```

The way it currently works is a bit annoying. When I find time I will

 1. let it write to stdout 
 2. let it read a message from stdin
 3. optionally encode by flipping bits, so that the original image is required to decode the message.
