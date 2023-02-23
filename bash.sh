#!/bin/bash
git commit -a -m"$1"
git checkout master
git merge dev
git checkout dev
