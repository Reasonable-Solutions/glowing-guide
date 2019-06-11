type state = option(string);
type action =
  | Upload(string);

module M = {
  [@bs.val] [@bs.scope "URL"]
  external createObjectURL: Webapi.File.t => string = "";
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
    <input
      type_="file"
      onChange={event => {
        let f = ReactEvent.Form.target(event)##files;
        upload(M.createObjectURL(f[0]));
        dispatch(Upload(f[0]##name));
      }}
    />
    {switch (state) {
     | None => ReasonReact.null
     | Some(file) => <p> {ReasonReact.string(file)} </p>
     }}
  </div>;
};
