module Info = {
    let version = "0.1.0";
    let description = "dune-fmt is a very opinionated dune pretty printer";
    let repo = "https://github.com/davesnx/dune-fmt";
    let bugUrl = repo ++ "/issues";
};

let readFile = filename => {
  open Core;
  let file = In_channel.create(filename);
  let strings = In_channel.input_lines(file);
  In_channel.close(file);
  strings |> String.concat(~sep=" ");
};

let writeFile = (filename, text) => {
  open Core;
  let outc = Out_channel.create(~append=false, filename);
  Out_channel.output_string(outc, text);
  Out_channel.close(outc);
};

let run = (path: string, inplace: bool) => {
  let content = readFile(path);
  let formatted = Source.Main.main(content);
  inplace ? writeFile(path, formatted) : print_endline(formatted);
};

open Cmdliner;
open Term;

let path = {
  Arg.(
    value
    & pos(0, string, "./dune")
    & info([], ~doc="dune file"));
};

let inplace = {
  Arg.(
    value
    & opt(bool, true)
    & info(["w", "write-in-place"], ~doc="Write down the file with the new format")
  );
};

let cmd = (
  Term.(const(run) $ path $ inplace),
  Term.info(
    "dune-fmt",
    ~version=Info.version,
    ~doc="Pretty print dune files",
    ~exits=Term.default_exits,
    ~man=[
      `S(Manpage.s_description),
      `P(Info.description),
      `P("dune-fmt './dune'"),
      `S(Manpage.s_bugs),
      `P("Report them to " ++ Info.bugUrl),
    ],
  ),
);

cmd |> eval |> exit;

