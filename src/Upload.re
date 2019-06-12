type state = option(string);
type action =
  | Upload(string);

module Url = {
  [@bs.val] [@bs.scope "URL"]
  external createObjectURL: Webapi.File.t => string = "";
};

module Styles = {
  open Css;
  let dropArea = style([background(goldenrod), padding(px(60))]);
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
      onDrop={event => {
        ReactEvent.Mouse.preventDefault(event);
        ReactEvent.Mouse.stopPropagation(event);
        let e = ReactEvent.Synthetic.nativeEvent(event);
        let files = e##dataTransfer##files;
        upload(Url.createObjectURL(files[0]));
        dispatch(Upload(files[0]##name));
      }}>
      {ReasonReact.string("drop")}
      <input
        type_="file"
        onChange={event => {
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
