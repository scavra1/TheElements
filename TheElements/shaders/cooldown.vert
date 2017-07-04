varying vec2 vTexCoord;

void main(void)
{
   vTexCoord = gl_MultiTexCoord0;
   gl_Position = ftransform();
}