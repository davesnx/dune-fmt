open Sexplib;
open Sexp;

let ident = num => String.make(num, ' ');
let renderWithTab = (~tab, str) => ident(tab) ++ str;

let renderInline = (~tab, str) => ident(tab) ++ "(" ++ str ++ ")"

let renderBox = (~insideList, ~tab, str) => {
  (insideList ? ident(tab) : "")
    ++ "(" ++ "\n" ++ str ++ "\n" ++ ident(tab) ++ ")";
};

let render = (expr: Sexp.t) => {
  let rec inner = (expr, ~tab, ~isInline, ~insideList) => {
    switch (expr) {
    | Atom(str) when isInline => str
    | Atom(str) => renderWithTab(~tab, str)
    | List([Atom(str), List(list)]) => {
      let identation = ident(tab);
      identation ++ "(" ++ str ++ "\n" ++ (renderRawList(list, ~tab) |> renderBox(~insideList=true, ~tab=tab + 1)) ++ "\n" ++ identation ++ ")";
    }
    | List(list) when List.length(list) <= 3 => {
      list
      |> List.map(inner(~tab=tab + 1, ~isInline=true, ~insideList=false))
      |> String.concat(" ")
      |> renderInline(~tab)
    }
    | List(list) => renderList(~tab, ~insideList, list)
    };
  } and renderList = (~insideList, ~tab, list) => {
    let head = List.hd(list);
    let tail = List.tl(list);

    String.concat("\n", [
      inner(~tab=tab + 1, ~isInline=false, ~insideList=false, head),
      tail
        |> List.map(inner(~tab=tab + 2, ~isInline=false, ~insideList=true))
        |> String.concat("\n")
    ]) |> renderBox(~insideList, ~tab);
  } and renderRawList = (~tab, list) => {
      list
      |> List.map(inner(~tab=tab + 2, ~isInline=false, ~insideList=true))
      |> String.concat("\n");
  }

  inner(expr, ~tab=0, ~isInline=false, ~insideList=false);
};

let _debug = (expression: Sexp.t) => {
  let rec inner = (expr) => {
    switch (expr) {
      | Atom(str) => "Atom(" ++ str ++ ")"
      | List(lst) => "List(" ++ (List.map(inner, lst) |> String.concat(" ")) ++ ")"
    }
  };

  inner(expression);
};

let main = (str) => {
  try (
    Sexp.of_string(str) |> render
  ) {
    | _ => {
      failwith("There was a problem parsing the content of the dune file")
    }
  }
};
