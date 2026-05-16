# Coursework Archive Guide

This repository is part of a broader effort to turn older coursework into a useful public portfolio archive.

## Archive Principles

- Preserve submitted source code unless a separate modernization branch or folder is clearly labeled.
- Add modern repository hygiene around the submission: README, build instructions, smoke tests, license notes, and artifact inventory.
- Be transparent about what was submitted, what was provided by the course, and what was added later.
- Keep personal learning context visible. The point is not to make old work look new; it is to show growth.
- Avoid exposing private data such as student IDs, addresses, phone numbers, account names, passwords, or other students' information.

## Recommended Structure For CS Repositories

```text
.
|-- .github/workflows/          # Build/test automation where practical
|-- docs/
|   |-- course-artifacts/       # Reports, rubrics, grades, feedback, screenshots
|   |-- ARCHIVE_GUIDE.md        # Shared archive approach
|   |-- COURSE_ARTIFACTS.md     # Inventory of what is included
|   `-- FEEDBACK_TEMPLATE.md    # Template for grade/feedback additions
|-- src or original files       # Preserve the submitted work
|-- README.md                   # Portfolio-readable overview
`-- LICENSE                     # License original work where appropriate
```

## Adding Grades And Feedback

When adding grades or instructor feedback, prefer a short markdown summary plus the original artifact when appropriate.

Use this pattern:

- grade or score
- date received
- rubric categories
- quoted feedback only when it is appropriate to share
- brief reflection on what changed in your understanding afterward
- whether the source code is preserved as submitted or later modernized elsewhere

## Modernization Notes

If a project is later improved, keep that separate from the original submission. Good options:

- `modernized/` folder with a new implementation
- `docs/MODERNIZATION_NOTES.md` with planned changes
- a separate branch named `modernized` or `portfolio-polish`

That keeps the archive honest while still showing current best practices.
