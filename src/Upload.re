type state = option(string);
type action =
  | Upload(string);

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
    style([background(goldenrod), padding(px(60)), display(block)]);
  let upload = style([display(none)]);
};
[@react.component]
let make = (~upload) => {
  let (state, dispatch) =
    React.useReducer(
      (_state, action) =>
        switch (action) {
        | Upload(filename) => Some(filename)
        },
      None,
    );
  <div>
    <label
      className=Styles.dropArea
      onDragOver={(event: ReactEvent.Mouse.t) => stopAll(event)}
      onDragEnter={event => stopAll(event)}
      onDragLeave={event => stopAll(event)}
      onDrop={event => {
        stopAll(event);
        ReactEvent.Mouse.preventDefault(event);
        let e = ReactEvent.Synthetic.nativeEvent(event);
        let files = e##dataTransfer##files;
        Js.log(files);
        upload(Url.createObjectURL(files[0]));
        dispatch(Upload(files[0]##name));
      }}>
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
    {switch (state) {
     | None => ReasonReact.null
     | Some(file) => <p> {ReasonReact.string(file)} </p>
     }}
  </div>;
};
