# Full ALU
Author: Junyan Tang

NetID: jt418

A text description of your design implementation
A brief one-sentence functionality description of each self-designed module

I used 3 16-bit RCA adder to build 1 32-bit CSA adder. Then implemented addition/subtraction module of simple ALU using this 32-bit CSA adder.

- `half_adder.v`:  
Image size. If you have rectangular images, make sure your image size is the maximum of the width and height
- `full_adder`: 
Number of patches. `image_size` must be divisible by `patch_size`.  
The number of patches is: ` n = (image_size // patch_size) ** 2` and `n` **must be greater than 16**.
- `mux`: 
Number of classes to classify.
- `mux_16`: 
Last dimension of output tensor after linear transformation `nn.Linear(..., dim)`.
- `RCA_16bits`: 
Number of Transformer blocks.
- `CSA_32bits`: 
Number of heads in Multi-head Attention layer. 
- `add_sub`: 
Dimension of the MLP (FeedForward) layer. 
- `and_logic`: int, default `3`.  
Number of image's channels. 
- `or_logic`: float between `[0, 1]`, default `0.`.  
Dropout rate. 
- `SLL`: float between `[0, 1]`, default `0`.  
Embedding dropout rate.
- `SRA`: string, either `cls` token pooling or `mean` pooling
- `alu`: string, either `cls` token pooling or `mean` pooling
