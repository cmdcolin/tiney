#define KERNEL_SIZE 9

//size of bigger "pixel regions". These regions are forced to be square
uniform int pixelSize; 

//dimensions in pixels of billboardTexture
uniform ivec2 billboardSize; 

//texure to be applied to billboard quad
uniform sampler2D billboardTexture; 

vec2 texCoords[KERNEL_SIZE]; //stores texture lookup offsets from a base case

void main(void)
{
     //will hold our averaged color from our sample points
     vec4 avgColor; 
     
     //width of "pixel region" in texture coords
     vec2 texCoordsStep = 1.0/(vec2(float(billboardSize.x),float(billboardSize.y))/float(pixelSize)); 
     
     //"pixel region" number counting away from base case
     vec2 pixelBin = floor(gl_TexCoord[0].st/texCoordsStep); 
     
     //width of "pixel region" divided by 3 (for KERNEL_SIZE = 9, 3x3 square)
     vec2 inPixelStep = texCoordsStep/3.0; 
     vec2 inPixelHalfStep = inPixelStep/2.0;

     //use offset (pixelBin * texCoordsStep) from base case 
     // (the lower left corner of billboard) to compute texCoords
     vec2 offset = pixelBin * texCoordsStep;
     
     texCoords[0] = vec2(inPixelHalfStep.x, inPixelStep.y*2.0 + inPixelHalfStep.y) + offset;
     texCoords[1] = vec2(inPixelStep.x + inPixelHalfStep.x, inPixelStep.y*2.0 + inPixelHalfStep.y) + offset;
     texCoords[2] = vec2(inPixelStep.x*2.0 + inPixelHalfStep.x, inPixelStep.y*2.0 + inPixelHalfStep.y) + offset;
     texCoords[3] = vec2(inPixelHalfStep.x, inPixelStep.y + inPixelHalfStep.y) + offset;
     texCoords[4] = vec2(inPixelStep.x + inPixelHalfStep.x, inPixelStep.y + inPixelHalfStep.y) + offset;
     texCoords[5] = vec2(inPixelStep.x*2.0 + inPixelHalfStep.x, inPixelStep.y + inPixelHalfStep.y) + offset;
     texCoords[6] = vec2(inPixelHalfStep.x, inPixelHalfStep.y) + offset;
     texCoords[7] = vec2(inPixelStep.x + inPixelHalfStep.x, inPixelHalfStep.y) + offset;
     texCoords[8] = vec2(inPixelStep.x*2.0 + inPixelHalfStep.x, inPixelHalfStep.y) + offset;

     //take average of 9 pixel samples
     avgColor = texture2D(billboardTexture, texCoords[0]) +
                         texture2D(billboardTexture, texCoords[1]) +
                         texture2D(billboardTexture, texCoords[2]) +
                         texture2D(billboardTexture, texCoords[3]) +
                         texture2D(billboardTexture, texCoords[4]) +
                         texture2D(billboardTexture, texCoords[5]) +
                         texture2D(billboardTexture, texCoords[6]) +
                         texture2D(billboardTexture, texCoords[7]) +
                         texture2D(billboardTexture, texCoords[8]);

     avgColor /= float(KERNEL_SIZE);

     gl_FragColor = avgColor;
}
