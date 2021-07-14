## Fast Inverse Square Root.

Inverse square roots are implemented on fragment and vertex shaders to decrease the time it takes to display an object.

There are many limits to what you can do with a inverse square root, games like Quake 3 and TF1, utilize this algorithm to it's fullest.



The following algorithm implemented in this case, is threaded on basis of how many CPU cores the user running has.

But that's a bunch of buzz words, so let's just put up an example.

Let's say we have some fragment shader code written up on your favorite code editor, such as this:

```c++
#version 330 core
out vec4 FragColor;
void main() // Don't question this setup, you can change these float values to make shaders for the object rendered.
{
  FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
};
```

Alright that looks pretty standard, and the variable for the fragment shader is marked by `FragColor`, as a disclaimer for those new to OpenGL (Why are you here?).

But in fact, the type `vec4` can be also written as a float value, it's just a specific type that works with other functions.

So we could do say in our main function, with the header file installed, to make it faster.

```c++
GLfloat frag4 = InvSqrt(FragColor);
```

`frag4` in this case, will hold a new version of the shader object, that is normalized to display color, shader properties on the screen, much, much, faster.

We can also do this with vertex shaders.

```c++
version 330 core
layout (location = 0) in vec3 aPos;

out vec4 gl_Position;
void main() // You don't really need to change anything here.
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}; 
```



The variable `gl_Position` can be normalized,

so once again we'd run our function on that variable, and we'd normalize all of the objects using the vertex shader.



There's also a much deeper thing to just applying it to simple float variables.

Say your programming a collision to happen at point A..

Without normalization, it would look sort of like this.

![collision](https://i.ibb.co/mJDfRV6/collision.png)

See why this is a problem, because the object is flinging longer than the initial impact, that isn't realistic, sometimes the default physics that you programmed, will probably fling the object, to god knows where, so we to normalize the positions, we'd use the inverse square root to maybe give us more accurate results;

![collision2](https://i.ibb.co/n3Gdx7T/collision2.png)

Physics engines and fast rendering isn't also an issue, there's also when creating big games, having really bad FPS issues, because of how much the shaders take a toll on the GPU and CPU. Even so with a GPU being able to run a lot of tasks fairly quick.

Normalization helps us by dividing the shaders into literal zillions of tiny segments, that make it REALLY easy to render.



So there is a lot to be gained from inverse square root algorithms and it'll probably be the most efficient option out there to help render textures and models.
