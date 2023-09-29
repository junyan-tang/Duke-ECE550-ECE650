# Full ALU
Author: Junyan Tang

NetID: jt418

A text description of your design implementation
A brief one-sentence functionality description of each self-designed module

I used 3 16-bit RCA adder to build 1 32-bit CSA adder. Then implemented addition/subtraction module of simple ALU using this 32-bit CSA adder.

- `half_adder`: int.  
Image size. If you have rectangular images, make sure your image size is the maximum of the width and height
- `patch_size`: int.  
Number of patches. `image_size` must be divisible by `patch_size`.  
The number of patches is: ` n = (image_size // patch_size) ** 2` and `n` **must be greater than 16**.
- `num_classes`: int.  
Number of classes to classify.
- `dim`: int.  
Last dimension of output tensor after linear transformation `nn.Linear(..., dim)`.
- `depth`: int.  
Number of Transformer blocks.
- `heads`: int.  
Number of heads in Multi-head Attention layer. 
- `mlp_dim`: int.  
Dimension of the MLP (FeedForward) layer. 
- `channels`: int, default `3`.  
Number of image's channels. 
- `dropout`: float between `[0, 1]`, default `0.`.  
Dropout rate. 
- `emb_dropout`: float between `[0, 1]`, default `0`.  
Embedding dropout rate.
- `pool`: string, either `cls` token pooling or `mean` pooling
