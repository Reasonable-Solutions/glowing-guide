type state = {
  file: option(string),
  valid: bool,
};
type action =
  | Upload(string)
  | ValidDrag(bool)
  | Delete(string);

module Url = {
  [@bs.val] [@bs.scope "URL"]
  external createObjectURL: Webapi.File.t => string = "";
};

let stopAll = e => {
  ReactEvent.Mouse.preventDefault(e);
  ReactEvent.Mouse.stopPropagation(e);
};

module Styles = {
  open Css;
  let deleter = style([display(`flex)]);
  let deleteButton =
    style([
      display(inlineBlock),
      borderStyle(none),
      background(none),
      padding4(px(10), px(40), px(10), px(40)),
      hover([fontWeight(bold)]),
    ]);
  let dropStyle =
    style([
      background(Theme.lBlue),
      padding(px(60)),
      display(block),
      borderRadius(px(5)),
      boxShadow(~y=px(1), ~blur=px(2), Theme.textBlack),
    ]);

  let dropArea = valid =>
    switch (valid) {
    | false => merge([dropStyle, style([background(red)])])
    | true => merge([dropStyle])
    };

  let upload = style([display(none)]);
  let dropText = style([fontSize(px(16)), color(Theme.textBlack)]);
};
[@react.component]
let make = (~upload, ~delete) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Upload(filename) => {...state, file: Some(filename)}
        | Delete(_) => {...state, file: None}
        | ValidDrag(p) => {...state, valid: p}
        },
      {file: None, valid: true},
    );
  <div>
    <label
      className={Styles.dropArea(state.valid)}
      onDragOver={(event: ReactEvent.Mouse.t) => stopAll(event)}
      onDragEnter={event => {
        let items =
          ReactEvent.Synthetic.nativeEvent(event)##dataTransfer##items;
        if (items
            |> List.filter(a => a##_type != "image/png")
            |> (l => List.length(l) == 0)) {
          stopAll(event); // this is about signaling that the <label> is a valid dropTarget for only images
          dispatch(ValidDrag(true));
        } else {
          ReactEvent.Mouse.stopPropagation(event);
          dispatch(ValidDrag(false));
        };
      }}
      onDragLeave={event => {
        dispatch(ValidDrag(true));
        stopAll(event);
      }}
      onDrop={event => {
        stopAll(event);
        let e = ReactEvent.Synthetic.nativeEvent(event);
        let files = e##dataTransfer##files;
        upload(Url.createObjectURL(files[0]));
        dispatch(Upload(files[0]##name));
      }}>
      <span className=Styles.dropText> {React.string("Add file")} </span>
      <input
        className=Styles.upload
        type_="file"
        onChange={event => {
          ReactEvent.Form.preventDefault(event);
          ReactEvent.Form.stopPropagation(event);
          let f = ReactEvent.Form.target(event)##files;
          upload(Url.createObjectURL(f[0]));
          dispatch(Upload(f[0]##name));
        }}
      />
    </label>
    {switch (state.file) {
     | None => ReasonReact.null
     | Some(file) =>
       <div className=Styles.deleter>
         <p> {ReasonReact.string(file)} </p>
         <button
           className=Styles.deleteButton
           onClick={_e => {
             dispatch(Delete(file));
             delete(file);
           }}>
           {React.string("X")}
         </button>
       </div>
     }}
  </div>;
};
