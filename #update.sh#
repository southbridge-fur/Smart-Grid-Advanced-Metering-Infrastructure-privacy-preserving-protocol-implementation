#!/bin/bash
rm -rf src/* simulations/* doxygen/*
cp -r /home/daniel/omnetpp-5.0/samples/Smart3P/simulations/* ./simulations/
cp -r /home/daniel/omnetpp-5.0/samples/Smart3P/src/* ./src/
cp /home/daniel/omnetpp-5.0/samples/Smart3P/* ./

doxygen doxygen.config

git add *
git commit -m "$1"
git push
