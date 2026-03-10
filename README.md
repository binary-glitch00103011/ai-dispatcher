# AI Dispatcher (BETA / WORK-IN-PROGRESS)

> **WHAT IS THIS?**
> This is command line tool for collaborating with multiple AIs (like Gemini, Ollama, or specialized Linux AIs), this tool lets you talk to all of them from one single command in your terminal. Instead of opening different apps, you just type a simple shortcut, and this dispatcher sends your message to the right AI collaborator. It does not include AI agents, it pipes you prompts to the approprate AI based on a flag you set in the con fig file. It also allows you to pipe the response from one AI to another.

---


**SECURITY WARNING:**
This code currently does not sanitize against input and config injection.


### 🚀 Quick Start

If you just want to get this running, follow these three steps:

1. **Install:** Download the files, open your terminal in that folder, and type:
   `sudo make && sudo make install`
2. **Setup:** Edit the config file in your home folder at `.config/ai.conf` and list your AIs like this:
   `-g:gemini`
3. **Talk:** Type `ai -g Hello there!` and your message will be sent to Gemini instantly.


HEADS UP: This code is currently in beta status. I am building this as a 3-man digital team (me, binary-glitch [Human] PM, Gemini [AI] Architect, and Electra [AI] Inspector). It is released now for peer review and feedback.

Current Goal
Creating a lean, hardened C++ gateway for multiple AI providers (Gemini, Makulu, Llama/Ollama, etc.) using `execvp()` to bypass shell injection risks.

Seeking Feedback On:
• The `execvp()` argument handling logic.

• The plain-text `.conf` parser efficiency.

• Potential edge cases in Linux environment variable handling (`$HOME`).

The Philosophy
Built on the philosophy of treating AI has collaborative peers, & the principal of creating a simple command line that is stripped of typical modern bloat. It uses zero external libraries, relies on old-school C-style system calls, and will be hardened against shell injection using `execvp()`.

Features
• Provider Roster: Expand your AI team via a simple text file. (`~/.config/ai.conf`).

• Lean Build: Tiny memory footprint, perfect for older hardware or minimal distros and termal distros.

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
• Project Manager: (binary_glitch)

• Architect: Gemini (AI)

• Inspector: Electra (Makulu AI)
