#!/bin/bash
for map in maps/*; do
    echo "==> $map <=="
    ./cub3D "$map"
    echo ""
done
