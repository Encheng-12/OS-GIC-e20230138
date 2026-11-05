# Lab 3 — Wildcards and Links: individual report

Copy this template to `lab3/README.md` in your own course repository. Follow [the instructions](lab3-instruction.md).

- Student name/ID: e20230138
- Ubuntu username and environment: gic-teav-encheng
- Artifact paths (turn these into links after copying to your submission): `evidence/links.txt`, `evidence/replacement.txt`

## Original Prediction

**Prediction:** After `source.txt` is renamed to `renamed.txt`, the hard link (`hard.txt`) will still successfully read the old bytes because it points directly to the file's underlying inode (inode `18743715`), whereas the symbolic link (`soft.txt`) storing `source.txt` will break (become a dangling link) because it relies on the filename path lookup.

- **Reason:** A hard link creates an additional directory entry pointing to the same inode and data blocks, so renaming or moving the original file name leaves the inode and its link count intact. A symbolic link stores a literal text path string (`source.txt`). When the target file is renamed, the path string no longer resolves to a valid directory entry.
- **Captured:** Captured on paper/worksheet prior to running Task 2 Step 2.

## Test Evidence

Link to two short records under `evidence/`. Include enough command/input/output context to interpret them.

| Test | Claim | Result that would contradict it | Observed result | What remains unproven |
|---|---|---|---|---|
| two link types before rename | Hard and soft links correctly reference the source file | Inode numbers differ between hard link and source, or soft link points elsewhere | `source.txt` and `hard.txt` share inode `18743715` with link count 2; `soft.txt` (inode `18743793`) points to `source.txt` | Whether the filesystem enforces hard links across different partitions (not tested here) |
| dangling link and recreated filename | Hard link survives rename and preserves old data, while symlink breaks and new filename creates a new inode | Renaming `source.txt` breaks the hard link, or recreating `source.txt` reuses inode `18743715` | `cat soft.txt` failed with "No such file or directory"; new `source.txt` allocated inode `18743806` holding `version 2`, while `hard.txt` retained inode `18743715` holding `version 1` | Behavior when deleting all hard links while processes still have the file open |

## Explanation and Correction

- **Difference between links:** 
  - A **hard link** (`hard.txt`) points directly to the inode number (`18743715`) rather than a filename. It shares equal status with the original filename; renaming the source file only updates the directory entry name, leaving the underlying data blocks and inode untouched.
  - A **symbolic link** (`soft.txt`) is a separate file containing a text pointer (`-> renamed.txt`). It depends on filename resolution at runtime. When the target's name changes, the reference breaks until the symlink target path is updated.
- **Correction supported by observed results:** 
  Our initial prediction correctly anticipated that renaming `source.txt` would break the symbolic link while leaving the hard link fully functional. This was verified when `cat soft.txt` threw a "No such file or directory" error, whereas `cat hard.txt` successfully printed `version 1`. Furthermore, creating a new `source.txt` allocated a completely new inode (`18743806`), proving that filenames are merely labels pointing to inodes, and recreating a filename does not automatically re-link it to old inodes.

## AI Note (optional)

One useful suggestion and the test you used to verify it: Suggested verifying relative symbolic link path resolution from the target directory (`links/`) rather than the absolute workspace path, verified by checking `readlink soft.txt` output after recreation.

## Cleanup

No persistent background processes, network jobs, or custom filesystem mounts were created during this lab exercise; only local files and standard link entries were created within `$OSLAB_WORKSPACE/lab3`, so no manual process cleanup was required.