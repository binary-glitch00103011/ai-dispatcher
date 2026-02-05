AI Dispatcher (BETA / WORK-IN-PROGRESS)

# AI Dispatcher (BETA / WORK-IN-PROGRESS)

> **WHAT IS THIS?** (For novice & non-technical users)
> This is a "traffic controller" for AI. If you use multiple AI tools (like Gemini, Ollama, or specialized Linux AIs), this tool lets you talk to all of them from one single place in your terminal. Instead of opening different apps, you just type a simple shortcut, and this dispatcher sends your message to the right "AI Provider" for you.

---

### 🚀 Quick Start

If you just want to get this running, follow these three steps:

1. **Install:** Download the files, open your terminal in that folder, and type:
   `make && sudo make install`
2. **Setup:** Create a text file in your home folder at `.config/ai.conf` and list your AIs like this:
   `-g:gemini`
3. **Talk:** Type `ai -g Hello there!` and your message will be sent to Gemini instantly.


HEADS UP: This code is currently in "Draft" status. I am building this as a 3-man digital team (Human PM, Gemini Architect, and Electra Inspector). It is released now for peer review and feedback before I perform the final "Bare Metal" installation on my local machine.

Current Goal
Creating a lean, hardened C++ gateway for multiple AI providers (Gemini, Makulu, etc.) using `execvp()` to bypass shell injection risks.

Seeking Feedback On:
• The `execvp()` argument handling logic.

• The plain-text `.conf` parser efficiency.

• Potential edge cases in Linux environment variable handling (`$HOME`).

The Philosophy
Built on the principle of Survival of the Fittest, this dispatcher is stripped of all modern bloat. It uses zero external libraries, relies on old-school C-style system calls, and is hardened against shell injection using `execvp()`.

Features
• Provider Roster: Manage your AI "team" via a simple text file (`~/.config/ai.conf`).

• Lean Build: Tiny memory footprint, perfect for older hardware or minimal distros like BackBox.

• Security First: Bypasses the shell to prevent injection attacks.

• Multi-Word Support: No need for quotes; just type `ai -g how do I fix a segfault` and go.

Installation
1. Clone the repo.

2. Build the binary: `make`

3. Install to your path: `sudo make install`

Configuration
Create a file at `~/.config/ai.conf`:

```

# Flag:Command

-g:gemini

-e:makulu-ai

-o:ollama run llama3

```

The Team
• Project Manager: [User]

• Architect: Gemini (AI)

• Inspector: Electra (Makulu AI)

