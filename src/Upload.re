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
  let dropArea =
    style([
      background(Theme.lBlue),
      padding(px(60)),
      display(block),
      borderRadius(px(5)),
      boxShadow(~y=px(1), ~blur=px(2), rgba(0, 0, 0, 0.1)),
    ]);
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
        | Delete(filename) => {...state, file: None}
        | ValidDrag(p) => {...state, valid: p}
        },
      {file: None, valid: true},
    );
  <div>
    <label
      className=Styles.dropArea
      onDragOver={(event: ReactEvent.Mouse.t) => stopAll(event)}
      onDragEnter={event => {
        let items =
          ReactEvent.Synthetic.nativeEvent(event)##dataTransfer##items;
        if (items
            |> List.filter(a => a##_type != "image/png")
            |> (l => List.length(l) == 0)) {
          stopAll(
            event // this is about signaling that the <label> is a valid dropTarget for only images
          );
          dispatch(ValidDrag(true));
        } else {
          dispatch(ValidDrag(false));
        };
      }}
      onDragLeave={event => stopAll(event)}
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
       <div>
         <p> {ReasonReact.string(file)} </p>
         <button
           onClick={e => {
             dispatch(Delete(file));
             delete(file);
           }}>
           {React.string("X")}
         </button>
       </div>
     }}
  </div>;
};
