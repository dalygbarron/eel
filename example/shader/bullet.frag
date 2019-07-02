/**
 * The idea here is that it will rotate the hue of the bullet to a value that gets passed in so we can use just one
 * bullet sprite for a few different colours of bullet.
 * There is not really any performance cost to using a shader for the bullet but there might be if this is complex.
 * It should not be super bad though as it is just a rotation in 3d space where each colour is a dimension.
 */


uniform float time;

void main() {
    gl_FragColor = vec4(1.0, sin(time), cos(time * 2.0), 1.0 / (time / 2.0));
}
