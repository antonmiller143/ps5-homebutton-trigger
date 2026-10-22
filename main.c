name: PS5 ELF Compiler

on:
  push:
    branches: [ "main" ]
  workflow_dispatch:

jobs:
  build:
    runs-on: ubuntu-24.04
    env:
      ACTIONS_ALLOW_USE_UNSECURE_NODE_VERSION: true

    steps:
    - uses: actions/checkout@v4

    - name: Install Compiler
      run: |
        sudo apt-get update
        sudo apt-get install -y clang-18 lld-18 build-essential

    - name: Direct Compile Without SDK Overhead
      run: |
        # Wir backen die ELF-Datei direkt ueber Clang als stand-alone Payload fuer die PS5
        clang-18 -target x86_64-scei-ps4 -O2 -static -nostdlib \
          -Wl,--preserve-dates \
          -fuse-ld=lld-18 \
          main.c -o homebutton_trigger.elf

    - name: Upload Finished ELF
      uses: actions/upload-artifact@v4
      with:
        name: PS5-Homebutton-Payload
        path: homebutton_trigger.elf
