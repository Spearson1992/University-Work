using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using AForge.Imaging;
using AForge.Imaging.Filters;

namespace Rovio
{
    public enum FilterColour
    {
        Red,
        Blue,
        Green,
        White,
        Yellow
    }

    public class ImageProcessor
    {

        private Bitmap[] colourImagesBackBuffer;
        private Bitmap[] colourImagesFrontBuffer;
        protected Dictionary<FilterColour, HSLFiltering> filters;
        //buffer lock flag
        public bool swappingBuffers;
        
        //stores the largest object rectangle for each colour sliced image
        private Rectangle[] objectFrontBuffer;
        private Rectangle[] objectBackBuffer;

        /// <summary>
        /// Constructor
        /// </summary>
        public ImageProcessor()
        {
            colourImagesBackBuffer = new Bitmap[5];
            colourImagesFrontBuffer = new Bitmap[5];
            objectFrontBuffer = new Rectangle[5];
            objectBackBuffer = new Rectangle[5];
            swappingBuffers = false;
            SetUpColours();
        }
        
        /// <summary>
        /// Initialises the separate colour filters
        /// </summary>
        private void SetUpColours()
        {
            filters = new Dictionary<FilterColour, HSLFiltering>();

            //Red colour filter
            HSLFiltering filter = new HSLFiltering();
            filter.Hue = new AForge.IntRange(345, 20);
            filter.Saturation = new AForge.Range(0.6f, 1);
            filter.Luminance = new AForge.Range(0.2f, 0.67f);
            filters.Add(FilterColour.Red, filter);

            //Blue colour filter
            filter = new HSLFiltering(); 
            filter.Hue = new AForge.IntRange(200, 260);
            filter.Saturation = new AForge.Range(0.2f, 1.0f);
            filter.Luminance = new AForge.Range(0.2f, 0.67f);
            filters.Add(FilterColour.Blue, filter);

            //Green colour filter
            filter = new HSLFiltering();
            filter.Hue = new AForge.IntRange(90, 135);
            filter.Saturation = new AForge.Range(0.3f, 1.0f);
            filter.Luminance = new AForge.Range(0.2f, 0.67f);
            filters.Add(FilterColour.Green, filter);

            //Yellow colour filter
            filter = new HSLFiltering();
            filter.Hue = new AForge.IntRange(60, 78);
            filter.Saturation = new AForge.Range(0.2f, 0.8f);
            filter.Luminance = new AForge.Range(0.2f, 0.8f);
            filters.Add(FilterColour.Yellow, filter);

            //White colour filter
            filter = new HSLFiltering();
            filter.Hue = new AForge.IntRange(200, 240);
            filter.Saturation = new AForge.Range(0, 0);
            filter.Luminance = new AForge.Range(0, 0);
            filters.Add(FilterColour.White, filter);

        }

        /// <summary>
        /// Main image processing function
        /// </summary>
        /// <param name="image">Image to process</param>
        /// <param name="colours">Araay of colours to look for in the image</param>
        public void ProcessImages(Bitmap image, FilterColour[] colours)
        {
            Bitmap colourSliced;

            foreach (FilterColour colour in colours)
            {
                colourSliced = filters[colour].Apply(image); //aplly the filter
                colourImagesBackBuffer[(int)colour] = colourSliced; // store data to back buffer
            }

            Bitmap grayscale; // temporary bitmap to store image after being greyscaled for later use in blob counting
            //Setup the blob counter
            AForge.Imaging.BlobCounter blobs = new AForge.Imaging.BlobCounter();
            blobs.ObjectsOrder = ObjectsOrder.Size;
            blobs.MinWidth = 10;
            blobs.FilterBlobs = true;

            foreach (FilterColour colour in colours)
            {
                grayscale = Grayscale.CommonAlgorithms.Y.Apply(colourImagesBackBuffer[(int) colour]);

                blobs.ProcessImage(grayscale);
                if (blobs.ObjectsCount > 0)
                    objectBackBuffer[(int) colour] = blobs.GetObjectsInformation()[0].Rectangle;
                else
                    objectBackBuffer[(int) colour] = Rectangle.Empty;
               
            }
            //Swap buffers
            swappingBuffers = true;
                objectBackBuffer.CopyTo(objectFrontBuffer, 0);
                colourImagesBackBuffer.CopyTo(colourImagesFrontBuffer, 0);
            swappingBuffers = false;
        }
        /// <summary>
        /// Helper function to get detected objects
        /// </summary>
        /// <param name="colour">The object colour that the detection is wanted for</param>
        /// <returns></returns>
        public Rectangle GetObjectRectangle(FilterColour colour)
        {
            return objectFrontBuffer[(int)colour];
        }
        /// <summary>
        /// Helper function to get sliced images
        /// </summary>
        /// <param name="colour">The colour of the filter used for the image wanted</param>
        /// <returns></returns>
        public Bitmap GetColourSlicedImage(FilterColour colour)
        {
            return colourImagesFrontBuffer[(int)colour];
        }



    }
}
