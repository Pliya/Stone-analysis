# STONE-ANALYSIS

## Overview

**Stone Analysis** is an audio steganography and signal analysis project whose main goal is to **decrypt secret messages hidden inside sound waves** and **conceal custom messages inside audio files** without altering how they sound.

Working with **WAV audio files (16-bit PCM, mono-channel, 48 kHz sampling rate)**, the program allows you to:
1. **Decypher (`--decypher`)**: Extract and decode a secret message concealed within an audio file.
2. **Cypher (`--cypher`)**: Hide a secret message inside a WAV file while keeping the original header intact and the audio perceptually identical.
3. **Analyze (`--analyze`)**: Decompose the sound wave using Fourier transforms to find and display the top $N$ dominant frequencies.

---

## Technical Approach

### 1. Audio Steganography (LSB Algorithm)
To hide and retrieve secret messages without altering the perceived sound or file size, the program uses **Least Significant Bit (LSB)** steganography:
- **Cyphering**: The message is first reversed, then each character is converted into its 8-bit binary representation (terminated by a null byte). Each bit replaces the least significant bit of a consecutive 16-bit audio sample.
- **Decyphering**: The program reads the least significant bit of each audio sample in groups of 8 bits to reconstruct each character until the null byte is reached, then reverses the string back to reveal the original message.

### 2. Frequency Analysis (DFT & Cooley-Tukey FFT)
To analyze the audio signal and extract its main frequencies, the time-domain samples are transformed into the frequency domain:
- Uses the recursive **Cooley-Tukey Fast Fourier Transform (FFT)** algorithm in $O(N \log N)$ (alongside **DFT / IDFT / IFFT** implementations).
- Computes the magnitude of each frequency bin, sorts them in descending order, and displays the top $N$ strongest frequencies.

### 3. WAV Format Validation
Before processing, the program parses the **44-byte WAV header** to verify that the file is a valid **16-bit PCM, mono-channel, 48 kHz** audio file, and preserves the exact original header when generating a cyphered WAV file.

### 4. Error Management
The program validates command-line flags, message characters, numeric parameters, and WAV file integrity, and handles runtime crashes (such as segmentation faults) by outputting clear error messages and exiting with **code `84`**.

### 5. Bonus Features
- **Full ASCII Table Support**: Allows hiding and extracting any ASCII character (preserving uppercase/lowercase and special characters).
- **Spectral Visualization (`--graph`)**: Uses **SFML** to render the audio file's frequency spectrum calculated via FFT as a colored bar chart in a graphical window.

---

## Build Instructions

### Standard Version
```bash
make            # Build the stone_analysis binary
make clean      # Remove temporary and coverage files
make fclean     # Remove temporary files, stone_analysis, and unit_tests binaries
make re         # Rebuild the project from scratch
```

### Bonus Version (requires SFML)
```bash
cd Bonus
make
```

---

## Usage

### 1. Decrypt a Hidden Message from a WAV File (`--decypher`)
```bash
./stone_analysis --decypher <IN_FILE>
```
**Example:**
```bash
./stone_analysis --decypher output.wav
# MIAOU
```

### 2. Hide a Secret Message in a WAV File (`--cypher`)
```bash
./stone_analysis --cypher <IN_FILE> <OUT_FILE> "<MESSAGE>"
```
**Example:**
```bash
./stone_analysis --cypher tests/sine440.wav output.wav "Miaou"
```

### 3. Analyze Top $N$ Dominant Frequencies (`--analyze`)
```bash
./stone_analysis --analyze <IN_FILE> <N>
```
**Example:**
```bash
./stone_analysis --analyze tests/sine440.wav 3
# Top 3 frequencies:
# 440 Hz
# ...
```

### 4. Spectral Visualization (Bonus Only)
```bash
./Bonus/stone_analysis --graph tests/sine440.wav
```

---

## Unit Tests

The test suite uses the **Criterion** testing framework to validate input checking, valid and invalid WAV file parsing, and message injection/extraction:

```bash
make tests_run
```
