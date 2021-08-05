#!/bin/bash

temp_render_path=$(realpath ./render-build-temp)
input_blender_file=$(realpath $1)
output_sprite_sheet_path=$(realpath $2)
output_filename_prefix=$3

blender -v &>/dev/null
if [ $? -ne 0 ]; then
    echo "Can't find Blender in PATH. Blender >=2.9 is required."
    exit
else
    echo "Found Blender: '$(which Blender)'"
fi

if [ -d $temp_render_path ]; then
    echo "Deleting animation render working directory ($temp_render_path)"
    rm -r $temp_render_path
fi

if [ ! -d $temp_render_path ]; then
    echo "Recreating animation render working directory ($temp_render_path)"
    mkdir $temp_render_path
fi

blender -b $input_blender_file --use-extension 1 -s 1 -o $temp_render_path/$output_filename_prefix --render-anim 

if [ $? -ne 0 ]; then
    echo "Blender exited with a non-zero exit code. Render failed."
else
    echo "Rendered animation frames to $temp_render_path"
fi

montage -version &>/dev/null
if [ $? -ne 0 ]; then
    echo "Unable convert the animation frames from Blender into a sprite sheet. ImageMagick (montage command) is required."
    exit
else
    echo "Found montage (ImageMagick): '$(which montage)'"
fi

montage $temp_render_path/$output_filename_prefix*.png -tile 10x3 -geometry 256x128+0+0 -background transparent $output_sprite_sheet_path
if [ $? -ne 0 ]; then
    echo "Failed to convert animation frames into sprite sheet"
    exit
else
    echo "Converted animation frames into sprite sheet ($output_sprite_sheet_path)"
fi
