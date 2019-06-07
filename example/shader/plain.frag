
uniform float time;
uniform vec2 resolution;

#define R resolution
#define T time

#define sin01(_a) .5 + .5 * sin(_a)

mat2 rotate(float a) {

    float c = cos(a);
    float s = sin(a);

    return mat2(c, s, -s, c);

}

vec3 camera(vec2 uv, vec3 ro, vec3 cl, vec3 cu) {

    vec3 cw = normalize(cl - ro);
    vec3 cr = normalize(cross(cu, cw));
    cu = normalize(cross(cw, cr));

    return normalize(uv.x * cr + uv.y * cu + cw);

}

void main() {

    vec2 uv = (2. * gl_FragCoord.xy - R) / R.y;

    vec3 col = vec3(0);

    vec3 ro = vec3(0.0, 0.0, -1);
    vec3 rd = camera(uv, ro, vec3(0, sin(T / 4.), 0), vec3(0.0, 1.0, 0.0));
    vec3 p = vec3(0);


    float d = 0.0;
    float t = 0.0;
    for (int i = 0; i < 100; i++) {
        p = ro + rd * t;

        d = 10. -(length(p) - 1.);
        if (d < 0.001) break;
        t += 0.5 * d;

    }

    if (d < 0.001) {

	    float k = time / 10.;
	    for (int i = 0; i < 3; i++) {
		    k += .5;
		    float s = .5;
		    for (int i = 0; i < 16; i++) {
			p = abs(p) - s;
			   p.xz *= rotate(k);
			    p.xy *= rotate(k);
			    p.yz *= rotate(k);
			s *= .95;

		    }
		    col[i] = .1 / abs(sin(length(p.xz * 2.) * 4.)) * .33;
		    col[i] += .1 / abs(sin(length(p.xy * 2.) * 4.)) * .33;
		    col[i] += .1 / abs(sin(length(p.yz * 2.) * 4.)) * .33;
    		}




    }





    gl_FragColor = vec4(col, 1.) * gl_Color;


}
