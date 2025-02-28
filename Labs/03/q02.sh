#!/bin/bash
echo "Enter a sentence"
read sentence
vowel_count=$(echo "$sentence" | grep -o -i "[aeiou]" | wc -l)
echo "Number of vowels in a sentence: $vowel_count"
