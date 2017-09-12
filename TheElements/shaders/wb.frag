uniform sampler2D texture;
uniform bool pause;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
	if(pause)
	{
		float med = (color.x + color.y + color.z) / 3;
		color = vec4(med, med, med, color.w);
	}
    gl_FragColor = color;
}