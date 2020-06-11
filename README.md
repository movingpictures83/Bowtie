# Language: C++
# Input: TXT
# Output: prefix
# Tested with: PluMA 1.0, GCC 4.8.4

PluMA plugin that interfaces to Bowtie (Langmead et al, 2009).

The plugin accepts as input a text file of keyword-value pairs,
whitespace-delimited:
contigs: Fasta file for contigs
sequences: Input sequences

All generated output files from Bowtie begin with the user-specified prefix

This plugin assumes Bowtie is in the system PATH.
