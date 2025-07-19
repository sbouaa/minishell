git clone https://github.com/username/repo.git  # Clone repo
cd repo                                        # Enter repo
2. Branching
bash
Copy
git checkout -b branch-name       # Create & switch to new branch
git checkout main                 # Switch to main branch
git branch -a                     # List all branches
3. Syncing Changes
bash
Copy
git pull origin main             # Update local main branch
git push -u origin branch-name   # Push branch to GitHub (first time)
git push                         # Push commits (after first push)
4. Committing
bash
Copy
git status                       # Check changed files
git add file.txt                 # Stage a file
git add .                        # Stage all changes
git commit -m "Your message"     # Commit changes
5. Merging & Pull Requests
bash
Copy
git checkout main               # Switch to main
git pull origin main            # Pull latest main
git merge branch-name           # Merge branch into main
6. Fixing Mistakes
bash
Copy
git stash                       # Save uncommitted changes temporarily
git stash pop                   # Restore stashed changes
git reset --hard HEAD           # Discard local changes (⚠️ careful)
7. Remote Management
bash
Copy
git remote -v                   # Check linked remote repo
git fetch                       # Fetch remote changes without merging