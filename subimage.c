#include "libbmp.h"
#include <stdio.h>
int matchindex = 0, match = 0;
int width_match_index(bmp_pixel **smallpx, bmp_pixel **bigpx, int smallwidth, int bigwidth, int sline, int bline, int index)
{
        int i, j;
        if (index > bigwidth - smallwidth)
        {
                printf("Wrong index %d\n", index);
                return -2;
        }
        for (i = index; i <= bigwidth - smallwidth; i++)
        {
                for (j = 0; j < smallwidth; j++)
                {
                        if ((smallpx[sline][j].red == bigpx[bline][i + j].red) && (smallpx[sline][j].green == bigpx[bline][i + j].green) &&
                            (smallpx[sline][j].blue == bigpx[bline][i + j].blue))
                                continue;
                        else
                                break;
                }
                if (j == smallwidth)
                {
                        matchindex = i;
                        return 0;
                }
                if (match == 1)
                        break;
        }
        return -1;
}

int main()
{
        bmp_pixel **bigpx, **smallpx;
        bmp_img fullimg, subimg;
        bmp_img_read(&fullimg, "full_image.bmp");
        bmp_img_read(&subimg, "sub_image.bmp");
        bigpx = fullimg.img_pixels;
        smallpx = subimg.img_pixels;
        int smallwidth = subimg.img_header.biWidth;
        int smallheight = subimg.img_header.biHeight;
        int bigwidth = fullimg.img_header.biWidth;
        int bigheight = fullimg.img_header.biHeight;
        int y = 0, z = 0, index = 0;
        for (y = 0; y <= bigheight - smallheight; y++)
        {
                if (width_match_index(smallpx, bigpx, smallwidth, bigwidth, 0, y, index) == 0)
                {
                        match = 1;
                        for (z = 1; z < smallheight; z++)
                        {
                                if (width_match_index(smallpx, bigpx, smallwidth, bigwidth, z, y + z, matchindex) == 0)
                                        continue;
                                else
                                        break;
                        }
                        if (z == smallheight)
                        {
                                printf("Match found at (%d, %d)\n", matchindex, y);
                                return 0;
                        }
                        match = 0;
                }
                else
                {
                        y++;
                        index = -1;
                }
                if (index < bigwidth - smallwidth)
                {
                        index++;
                        y--;
                }
                else
                        index = 0;
        }
}
