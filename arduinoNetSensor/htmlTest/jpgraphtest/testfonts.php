 <?php
      // Change this defines to where Your fonts are stored 
      DEFINE("TTF_DIR","/usr/X11R6/lib/X11/fonts/truetype/");
      // Change this define to a font file that You know that You have
      DEFINE("TTF_FONTFILE","arial.ttf");

      $f = TTF_DIR.TTF_FONTFILE;
      if( file_exists($f) === false || is_readable($f) === false ) {
          echo "FAIL: Can not read font file \"$f\".";
      }
      else {
          echo "PASS: Successfully read font file \"$f\".";
      }
      ?>
