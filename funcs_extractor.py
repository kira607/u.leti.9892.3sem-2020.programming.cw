import os 

if __name__ == "__main__":
    base_path = "/home/kirill/Universety/2_COURSE/1_SEM/PROGRAMMING/CR/report/modules/chapters/7-functions-description/"
    write_path = "/home/kirill/Universety/2_COURSE/1_SEM/PROGRAMMING/CR/report/modules/chapters/9-programm-algorithm/"
    # algo_path = "/home/kirill/Universety/2_COURSE/1_SEM/PROGRAMMING/CR/report/modules/chapters/algo.tex"
    paths = os.listdir(base_path)
    for path in paths:
        with open(base_path + path, "r") as f:
            content = f.read()
        # with open(algo_path, "a") as f:
        #     f.write(f'\\input{{modules/chapters/9-programm-algorithm/{path}}}\n')
        with open(write_path + path, "w") as f:
            tw = path[0:path.find(".tex")].replace("_", "\_")
            to_write = f"\\subsection{{Модуль {tw}}}" + "\n\n"
            s = 0
            e = 0
            while s > -1:
                s = content.find("\\subsubsection", e)
                if s == -1: continue
                print("found start on ", s)
                e = content.find("\n", s)
                tw = content[s:e]
                tw = tw[tw.find("{")+1:tw.find("}")]
                to_write += f"\\subsubsection{{{tw}}}" + "\n\n"
                to_write += "\\begin{lstlisting}\n    lst\n\\end{lstlisting}\n\n"
                to_write += "\\begin{itemize}\n    \\item \\verb||\n\\end{itemize}\n\n"
            f.write(to_write)
        