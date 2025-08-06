import re
import math
import sys

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
    try:
        with open('Goals_And_Steps.md', encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        print(f"Could not open Goals_And_Steps.md: {e}", file=sys.stderr)
        sys.exit(1)

    # Extract Goals and Next Steps sections
    goals_match = re.search(r'## Goals([\s\S]+?)(?=##|$)', content)
    next_match = re.search(r'## Next Steps([\s\S]+?)(?=##|$)', content)
    goals = goals_match.group(1) if goals_match else ''
    next_steps = next_match.group(1) if next_match else ''

    re_x = r'- \[x\]'
    re_ip = r'- \[(⏳|😰|🧩|🚩)\]'
    re_n = r'- \[ \]'

    g_c = count_matches(goals, re_x)
    g_i = count_matches(goals, re_ip)
    g_n = count_matches(goals, re_n)

    n_c = count_matches(next_steps, re_x)
    n_i = count_matches(next_steps, re_ip)
    n_n = count_matches(next_steps, re_n)

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
        with open('Goals_And_Steps.md', 'w', encoding='utf-8') as f:
            f.write(content)
    except Exception as e:
        print(f"Could not write Goals_And_Steps.md: {e}", file=sys.stderr)
        sys.exit(1)

    print("Progress bars and stats updated!")

if __name__ == '__main__':
    main()
