# Lab 4 — Redirection and Pipelines: individual report

Follow the [instruction](lab4-instruction.md). Copy this template into your own `lab4/README.md`. No script is required. Prediction/debrief/checkpoint answers stay in `oslab` records.

- Name / student ID: Teav Encheng / e20230138
- Linux account: gic-teav-encheng
- Personal status and other word: status = sent, other = pass

## Commands I Used

Save your actual commands, one per line, in `evidence/commands.txt`. Do not execute that file as a script.

| Stage | My command | Input received | Output produced |
|---|---|---|---|
| Select exact first field | `grep '^sent,' data/events.csv \| tee evidence/selected.txt` | Lines from `data/events.csv` (stdin for `tee` from `grep` stdout) | The 3 full CSV rows starting with `sent,` printed to terminal and saved to `evidence/selected.txt` |
| Extract field 2 | `grep '^sent,' data/events.csv \| cut -d, -f2 \| tee evidence/fields.txt` | The 3 matching `sent,` lines piped from `grep` stdout | The 3 numeric quantities (field 2) printed to terminal and saved to `evidence/fields.txt` |
| Count selected records | `grep '^sent,' data/events.csv \| wc -l > evidence/normal.txt` | The 3 matching `sent,` lines piped from `grep` stdout | Line count `3` written to `evidence/normal.txt` |
| Save stdout and stderr separately | `cat data/missing.csv > evidence/stdout.txt 2> evidence/stderr.txt` | Attempted file read of `data/missing.csv` | Empty `evidence/stdout.txt` (0 bytes) and `cat` missing-file error message in `evidence/stderr.txt` |
| Save exit status immediately | `echo $? > evidence/status.txt` | Shell exit status variable `$?` from `cat` | Nonzero exit code (`1`) saved in `evidence/status.txt` |

## What My Tests Show

| Test | Expected | Observed | Mistake it would catch |
|---|---|---|---|
| Original records | 3 exact matches | 3 matching rows in `selected.txt`, 3 quantities in `fields.txt`, count `3` in `normal.txt` | Summing quantities instead of counting records, or including header/other statuses |
| No match | 0 records | `0` on line 1 of `evidence/edge.txt` | False positives when the target status (`sent`) does not appear in the input |
| One added match plus a look-alike | 4 records | `4` on line 2 of `evidence/edge.txt` (`0` then `4`) | Prefix matching (counting `sent-late,99`), adding quantity (`7` instead of `1` row), or overwriting `edge.txt` with `>` instead of `>>` |
| Missing input | empty stdout, diagnostic on stderr, nonzero status | `stdout.txt` is empty, `stderr.txt` contains `cat: data/missing.csv: No such file or directory`, `status.txt` is `1` | Mixing error messages into normal output or checking `$?` too late after another command resets it |

## Explain the Commands

1. **Why does the comma in `grep '^WORD,'` matter?**
   The comma marks the end of the first CSV field. Without `,`, `grep '^sent'` would also match prefix look-alikes such as `sent-late,99` instead of requiring an exact match on the first column.

2. **Why does `wc -l` count records here, rather than add quantities?**
   `wc -l` counts newline-terminated lines received on stdin—one line per matching CSV record—without parsing or summing the numeric values in the second column.

3. **Where did you use `>>`, and what would `>` do instead?**
   `>>` was used in `grep '^sent,' data/changed.csv | wc -l >> evidence/edge.txt` (and in the guided `practice.txt` step) to append the second count (`4`) below the first count (`0`). Using `>` instead would truncate/overwrite `edge.txt` and erase the earlier `0` result.

4. **What does `tee` do that `>` alone does not?**
   `tee` splits stdout so it is both displayed on the terminal screen and written to a file simultaneously, whereas `>` redirects stdout silently into the file without displaying it on screen.

5. **Why must `echo $?` immediately follow the command being checked?**
   The shell updates `$?` after every foreground command finishes. Running any intermediate command (such as `cat` or `ls`) overwrites `$?` with that new command's exit status before you can record the original command's status.

6. **Why can `cat missing-file | wc -l` report pipeline status 0?**
   By default, a pipeline's exit status (`$?`) is the exit status of its **last** command (`wc -l`), not the first (`cat`). Even though `cat` fails and prints a diagnostic to stderr, `wc -l` reads 0 bytes from stdin, outputs `0`, and exits with status `0`.

## Limits and Evidence

These commands assume simple comma-separated text without quoted commas. Saved results describe one run; they do not prove every future input works or who typed a command.

Check the submission tree in the instruction: include `checkpoint.txt` and all required evidence files, including the empty `stdout.txt`. No `report.sh` is required.

## Optional Work / AI Note

- **Plus (`grep '^sent,' data/no-match.csv` followed by `echo $?`):** Printed no matching lines and returned exit status `1` with no stderr message, distinguishing a valid file with zero matches (`status 1`) from a missing file error in `cat` (stderr diagnostic + nonzero status).
- **Challenge (`cat data/events.csv data/missing.csv 2>&1 | tee evidence/challenge.txt`):** Placing `2>&1` before the pipe merges stderr into stdout so both the contents of `data/events.csv` and the `missing.csv` diagnostic enter `tee`, displaying and saving both streams together.
- **AI Note:** Used AI to review command syntax, verify redirection/pipeline concepts, and format this `README.md` report after completing the prediction and checkpoint questions independently.