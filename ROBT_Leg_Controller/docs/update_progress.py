import os
import re
import sys

def get_goals_path():
    cwd = os.getcwd()
    if os.path.basename(cwd).lower() == "docs":
        return "Goals_And_Steps.md"
    else:
        return os.path.join("docs", "Goals_And_Steps.md")

# Helper functions
def count_matches(text, pattern):
    return len(re.findall(pattern, text))

def make_bar(complete, in_progress, not_started, total_bars=30):
    total = complete + in_progress + not_started
    if total == 0:
        return '⬜' * total_bars
    c = round(complete / total * total_bars)
    i = round(in_progress / total * total_bars)
    n = total_bars - c - i
    return '🟩' * c + '🟨' * i + '⬜' * n

def percent(part, total):
    if total == 0:
        return '0'
    return str(int(round(100.0 * part / total)))

# Main logic
def main():
    goals_path = get_goals_path()
    try:
        with open(goals_path, encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        print(f"Could not open {goals_path}: {e}", file=sys.stderr)
        sys.exit(1)


    # Extract Goals and Next Steps sections (including all content until next ## header)
    goals_match = re.search(r'^## Goals[\s\S]+?(?=^## |\Z)', content, re.MULTILINE)
    next_match = re.search(r'^## Next Steps[\s\S]+?(?=^## |\Z)', content, re.MULTILINE)
    goals = goals_match.group(0) if goals_match else ''
    next_steps = next_match.group(0) if next_match else ''

    # Count checklist items anywhere within the section, regardless of ### headers
    re_x = r'^\s*- \[x\]' # completed
    re_ip = r'^\s*- \[(⏳|😰|🧩|🚩)\]' # in progress
    re_n = r'^\s*- \[ \]' # not started

    g_c = len(re.findall(re_x, goals, re.MULTILINE))
    g_i = len(re.findall(re_ip, goals, re.MULTILINE))
    g_n = len(re.findall(re_n, goals, re.MULTILINE))

    n_c = len(re.findall(re_x, next_steps, re.MULTILINE))
    n_i = len(re.findall(re_ip, next_steps, re.MULTILINE))
    n_n = len(re.findall(re_n, next_steps, re.MULTILINE))

    t_c = g_c + n_c
    t_i = g_i + n_i
    t_n = g_n + n_n
    g_total = g_c + g_i + g_n
    n_total = n_c + n_i + n_n
    t_total = t_c + t_i + t_n

    goals_bar = make_bar(g_c, g_i, g_n)
    next_bar = make_bar(n_c, n_i, n_n)
    total_bar = make_bar(t_c, t_i, t_n)

    goals_stats = f"Complete: {percent(g_c, g_total)}% | In Progress: {percent(g_i, g_total)}% | Not Started: {percent(g_n, g_total)}%"
    next_stats = f"Complete: {percent(n_c, n_total)}% | In Progress: {percent(n_i, n_total)}% | Not Started: {percent(n_n, n_total)}%"
    total_stats = f"Complete: {percent(t_c, t_total)}% | In Progress: {percent(t_i, t_total)}% | Not Started: {percent(t_n, t_total)}%"

    # Replace the progress bars and stats in the file
    total_re = re.compile(r'(\*\*Total Progress:\*\*\s*\n)[^\n]*\n[^\n]*\n')
    goals_rebar = re.compile(r'(\*\*Goals Progress:\*\*\s*\n)[^\n]*\n[^\n]*\n')
    next_rebar = re.compile(r'(\*\*Next Steps Progress:\*\*\s*\n)[^\n]*\n[^\n]*\n')

    content = total_re.sub(rf'\1{total_bar}  \n{total_stats}\n', content)
    content = goals_rebar.sub(rf'\1{goals_bar}  \n{goals_stats}\n', content)
    content = next_rebar.sub(rf'\1{next_bar}  \n{next_stats}\n', content)

    try:
        with open(goals_path, 'w', encoding='utf-8') as f:
            f.write(content)
    except Exception as e:
        print(f"Could not write {goals_path}: {e}", file=sys.stderr)
        sys.exit(1)

    print("Progress bars and stats updated!")

if __name__ == '__main__':
    main()
