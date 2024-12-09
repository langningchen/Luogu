#!/bin/bash
./P3870.gen >./P3870.in
./P3870 <./P3870.in >./P3870.out
./P3870.bf <./P3870.in >./P3870.bf.out
diff --color=always ./P3870.out ./P3870.bf.out
