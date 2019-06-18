/* State declaration */
type state = {
  file: option(string),
  title: string,
};

/* Action declaration */
type action =
  | UploadFile(string)
  | DeleteFile(string)
  | UpdateText(string);

module Styles = {
  open Css;
  global("body", [margin(px(0))]);
  global(
    "*",
    [
      boxSizing(borderBox),
      fontFamily("Helvetica Neue, Segoe UI, arial, sans-serif"),
    ],
  );

  let main =
    style([display(flexBox), height(vh(100.0)), background(Theme.grey)]);
  let sidebar =
    style([borderRight(px(1), solid, hex("d1d8db")), width(px(340))]);
  let content = style([]);
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | UploadFile(url) => {...state, file: Some(url)}
        | DeleteFile(_url) => {...state, file: None}
        | UpdateText(title) => {...state, title}
        },
      {file: None, title: ""},
    );
  <div className=Styles.main>
    <div className=Styles.sidebar>
      <Expander title="Image upload">
        <Upload
          upload={e => dispatch(UploadFile(e))}
          delete={e => dispatch(DeleteFile(e))}
        />
      </Expander>
      <Expander title="Title text">
        <div>
          <TitleInput
            startText="title text"
            update={s => dispatch(UpdateText(s))}
          />
        </div>
      </Expander>
    </div>
    <div className=Styles.content> {ReasonReact.string("content")} </div>
    {switch (state.file) {
     | None => ReasonReact.null
     | Some(file) => <img src=file />
     }}
    <h1> {ReasonReact.string(state.title)} </h1>
  </div>;
};
