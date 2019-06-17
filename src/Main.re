/* State declaration */
type state = {
  file: string,
  title: string,
};

/* Action declaration */
type action =
  | Upload(string)
  | UpdateText(string);

module Styles = {
  open Css;
  global("body", [margin(px(-1))]);
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
        | Upload(url) => {...state, file: url}
        | UpdateText(title) => {...state, title}
        },
      {file: "", title: ""},
    );
  <div className=Styles.main>
    <div className=Styles.sidebar>
      <Expander title="Image upload">
        <Upload upload={e => dispatch(Upload(e))} />
      </Expander>
      <Expander title="Title text">
        <div>
          <TitleInput
            startText="placeholder text, my fren"
            update={s => dispatch(UpdateText(s))}
          />
        </div>
      </Expander>
    </div>
    <div className=Styles.content> {ReasonReact.string("content")} </div>
    <img src={state.file} />
    <h1> {ReasonReact.string(state.title)} </h1>
  </div>;
};
